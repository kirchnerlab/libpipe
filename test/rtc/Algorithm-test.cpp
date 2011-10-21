/*
 * AlgorithmRTC-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */
//#include <utilsRTC.hpp>
#include <libpipe/config.hpp>
#include <iostream>
#include "vigra/unittest.hxx"

#define private public
#define protected public
#include <libpipe/rtc/Algorithm.hpp>
#undef private
#undef protected
#include "libpipe/rtc/AlgorithmFactory.hpp"
#include <libpipe/rtc/SharedData.hpp>

#include <limits>

#include <cstring>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include "libpipe/ctc/Algorithm.hpp" //for timeval comparisons
/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */

using namespace libpipe::rtc;

/** A local class that derives from Algorithm.
 */
class MyAlgorithm : public Algorithm
{
    public:

        static Algorithm* create()
        {
            return new MyAlgorithm;
        }

        ~MyAlgorithm()
        {
        }
        virtual libpipe::Request& update(libpipe::Request& req)
        {
            LIBPIPE_REQUEST_TRACE(req, "Identity: copying value.");

            boost::shared_ptr<libpipe::rtc::SharedData<int> > in_ =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        this->getPort("intInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<int> > out_ =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        this->getPort("intOutput"));
            out_ = in_;
            this->updateMTime();
            return req;
        }
    private:
        MyAlgorithm() :
                Algorithm()
        {
            ports_["intInput"] = boost::make_shared<
                    libpipe::rtc::SharedData<int> >(new int);
            ports_["intOutput"] = boost::make_shared<
                    libpipe::rtc::SharedData<int> >(new int);
        }

        /** Register Filter in the FilterFactory
         *
         */
        static const bool registered_;

        static const bool registerLoader()
        {
            std::string ids = "MyAlgorithm";
            return AlgorithmFactory::instance().registerType(ids,
                MyAlgorithm::create);
        }
};
const bool MyAlgorithm::registered_ = registerLoader();

struct AlgorithmRTCTestSuite : vigra::test_suite
{

        /** Constructor.
         * The AlgorithmRTCTestSuite constructor adds all AlgorithmRTC tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        AlgorithmRTCTestSuite() :
                vigra::test_suite("rtc/Algorithm")
        {
            // add(testCase(&AlgorithmTestSuite::fail));
            add(testCase(&AlgorithmRTCTestSuite::testFreeOperators));
            add(testCase(&AlgorithmRTCTestSuite::testInitialization));
            add(testCase(&AlgorithmRTCTestSuite::testProcessRequest));
            add(testCase(&AlgorithmRTCTestSuite::testUpdateMTime));
            add(testCase(&AlgorithmRTCTestSuite::testNeedUpdate));
            add(testCase(&AlgorithmRTCTestSuite::testGetSet));
            add(testCase(&AlgorithmRTCTestSuite::testInitTime));
            add(testCase(&AlgorithmRTCTestSuite::testports));

        }

        /** Test free operators
         */
        void testFreeOperators()
        {
            timeval tv1, tv2;
            gettimeofday(&tv1, NULL);
            tv2 = tv1;
            shouldEqual(operator==(tv1, tv2), true);
            shouldEqual(operator==(tv2, tv1), true);
            shouldEqual(operator<=(tv1, tv2), true);
            shouldEqual(operator<=(tv2, tv1), true);
            tv2.tv_sec += 1;
            shouldEqual(operator==(tv1, tv2), false);
            shouldEqual(operator==(tv2, tv1), false);
            shouldEqual(operator<=(tv1, tv2), true);
            shouldEqual(operator<=(tv2, tv1), false);
            tv2 = Algorithm::MAX_TIME;
            shouldEqual(operator==(tv1, tv2), false);
            shouldEqual(operator==(tv2, tv1), false);
            shouldEqual(operator<=(tv1, tv2), true);
            shouldEqual(operator<=(tv2, tv1), false);
            tv1 = Algorithm::MAX_TIME;
            shouldEqual(operator==(tv1, tv2), true);
            shouldEqual(operator==(tv2, tv1), true);
            shouldEqual(operator<=(tv1, tv2), true);
            shouldEqual(operator<=(tv2, tv1), true);
        }

        /** Test if the max initialization worked.
         */
        void testInitialization()
        {
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            shouldEqual(a->getMTime(), Algorithm::MAX_TIME);
            delete a;
        }

        /** Test Algorithm::processRequest.
         */
        void testProcessRequest()
        {
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            libpipe::Request req(libpipe::Request::DELETE);
            a->processRequest(req);
            shouldEqual(a->getMTime(), Algorithm::MIN_TIME);
            delete a;
        }

        /** Test Algorithm::updateMTime().
         */
        void testUpdateMTime()
        {
            // check if the self-update works.
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            shouldEqual(a->needUpdate(), true);
            a->updateMTime();
            shouldEqual(a->needUpdate(), false);
            delete a;
        }

        /** Test Algorithm::needUpdate().
         */
        void testNeedUpdate()
        {
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            // we expect the need for an update right after construction
            shouldEqual(a->needUpdate(), true);
            // now set the time to now()
            timeval tv;
            gettimeofday(&tv, NULL);
            a->setMTime(tv);
            shouldEqual(a->needUpdate(), false);
            delete a;
        }

        /** Run GET/SET tests for all member variables.
         */
        void testGetSet()
        {
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            a->setMTime(a->getMTime());
            delete a;
        }

        void testInitTime()
        {
            timeval tv;
            tv.tv_sec = std::numeric_limits<time_t>::max();
            tv.tv_usec = std::numeric_limits<suseconds_t>::max();
            shouldEqual(tv, Algorithm::MAX_TIME);

            tv.tv_sec = std::numeric_limits<time_t>::min();
            tv.tv_usec = std::numeric_limits<suseconds_t>::min();
            shouldEqual(tv, Algorithm::MIN_TIME);
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            a->initMaxTime();
            a->initMinTime();
            delete a;
        }

        void testports()
        {
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            Algorithm* b = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");

            boost::shared_ptr<libpipe::rtc::SharedData<int> > i =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        a->getPort("intInput"));

            boost::shared_ptr<libpipe::rtc::SharedData<int> > input(
                new SharedData<int>());
            input->set(new int(10));
            b->setInput("intOutput", input);

            shouldEqual(
                *boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(b->getPort("intOutput"))->get(),
                10);

            shouldEqual(
                *boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(a->getPort("intInput"))->get()==10,
                false);

            a->connect(b, "intOutput", "intInput");

            shouldEqual(
                *boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(a->getPort("intInput"))->get(),
                10);

            bool thrown = false;
            try {
                a->getPort("blub");
            } catch (libpipe::utilities::Exception& e) {
                shouldEqual(
                    strncmp(e.what(),"Algorithm::getPort failed, the following port was not registered: blub",70),
                    0);
                thrown = true;
            }

            shouldEqual(thrown, true);

            thrown = false;
            try {
                a->setInput("blub", input);
            } catch (libpipe::utilities::Exception& e) {
                shouldEqual(
                    strncmp(e.what(),"Algorithm::setInput failed, the following port was not registered: blub",70),
                    0);
                thrown = true;
            }shouldEqual(thrown, true);

            delete a;
            delete b;

        }
};

/** The main function that runs the tests for class AlgorithmRTC.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    AlgorithmRTCTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

