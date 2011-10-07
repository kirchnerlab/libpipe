/*
 * AlgorithmRTC-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"

#include "libpipe/RTC/AlgorithmRTC.hpp"
#include "libpipe/RTC/LibpipeFactories.hpp"
#include <sys/time.h> // for gettimeofday
#include <limits>

#include "libpipe/Algorithm.hpp" //for timeval comparisons


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */

using namespace libpipe::rtc;

/** A local class that derives from Algorithm.
 */
class MyAlgorithm : public AlgorithmRTC
{
    public:

        static AlgorithmRTC* create()
        {
            return new MyAlgorithm;
        }

        ~MyAlgorithm()
        {
        }
        virtual libpipe::Request& update(libpipe::Request& req)
        {
            // dummy
            return req;
        }
    private:
        MyAlgorithm() :
                AlgorithmRTC()
        {
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
                vigra::test_suite("AlgorithmRTC")
        {
            // add(testCase(&AlgorithmTestSuite::fail));
            add(testCase(&AlgorithmRTCTestSuite::testFreeOperators));
            add(testCase(&AlgorithmRTCTestSuite::testInitialization));
            add(testCase(&AlgorithmRTCTestSuite::testProcessRequest));
            add(testCase(&AlgorithmRTCTestSuite::testUpdateMTime));
            add(testCase(&AlgorithmRTCTestSuite::testNeedUpdate));
            add(testCase(&AlgorithmRTCTestSuite::testGetSet));
            add(testCase(&AlgorithmRTCTestSuite::testInitTime));
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
            tv2 = AlgorithmRTC::MAX_TIME;
            shouldEqual(operator==(tv1, tv2), false);
            shouldEqual(operator==(tv2, tv1), false);
            shouldEqual(operator<=(tv1, tv2), true);
            shouldEqual(operator<=(tv2, tv1), false);
            tv1 = AlgorithmRTC::MAX_TIME;
            shouldEqual(operator==(tv1, tv2), true);
            shouldEqual(operator==(tv2, tv1), true);
            shouldEqual(operator<=(tv1, tv2), true);
            shouldEqual(operator<=(tv2, tv1), true);
        }

        /** Test if the max initialization worked.
         */
        void testInitialization()
        {
            AlgorithmRTC* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            shouldEqual(a->getMTime(), AlgorithmRTC::MAX_TIME);
            delete a;
        }

        /** Test Algorithm::processRequest.
         */
        void testProcessRequest()
        {
            AlgorithmRTC* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            libpipe::Request req(libpipe::Request::DELETE);
            a->processRequest(req);
            shouldEqual(a->getMTime(), AlgorithmRTC::MIN_TIME);
            delete a;
        }

        /** Test Algorithm::updateMTime().
         */
        void testUpdateMTime()
        {
            // check if the self-update works.
            AlgorithmRTC* a = AlgorithmFactory::instance().createObject(
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
            AlgorithmRTC* a = AlgorithmFactory::instance().createObject(
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
            AlgorithmRTC* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            a->setMTime(a->getMTime());
            delete a;
        }

        void testInitTime()
        {
            timeval tv;
            tv.tv_sec = std::numeric_limits<time_t>::max();
            tv.tv_usec = std::numeric_limits<suseconds_t>::max();
            shouldEqual(tv, AlgorithmRTC::MAX_TIME);

            tv.tv_sec = std::numeric_limits<time_t>::min();
            tv.tv_usec = std::numeric_limits<suseconds_t>::min();
            shouldEqual(tv, AlgorithmRTC::MIN_TIME);

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

