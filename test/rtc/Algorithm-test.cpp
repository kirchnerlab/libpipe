/*
 *
 * Copyright (c) 2011 David-Matthias Sichau
 * Copyright (c) 2010 Marc Kirchner
 *
 * This file is part of libpipe.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <libpipe/config.hpp>
#include <iostream>
#include "vigra/unittest.hxx"
#ifndef  _WIN32
    #define private public
    #define protected public
#endif
#include <libpipe/rtc/Algorithm.hpp>
#ifndef  _WIN32
    #undef private
    #undef protected
#endif
#include <libpipe/rtc/AlgorithmFactory.hpp>
#include <libpipe/rtc/SharedData.hpp>
#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/utilities/Parameters.hpp>

#include <limits>

#include <cstring>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include <libpipe/utilities/Time.hpp> //for timeval comparisons
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
        virtual void update(libpipe::Request& req)
        {
            LIBPIPE_PIPELINE_TRACE(req, "Identity: copying value.");

            boost::shared_ptr<libpipe::rtc::SharedData<int> > in_ =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        this->getPort("intInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<int> > out_ =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        this->getPort("intOutput"));
#ifdef ENABLE_THREADING
            out_->lock();
            in_->shared_lock();
#endif
            out_ = in_;
            this->updateMTime();
#ifdef ENABLE_THREADING
            out_->unlock();
            in_->unlock();
#endif
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
            add(testCase(&AlgorithmRTCTestSuite::testInitialization));
            add(testCase(&AlgorithmRTCTestSuite::testProcessRequest));
            add(testCase(&AlgorithmRTCTestSuite::testUpdateMTime));
            add(testCase(&AlgorithmRTCTestSuite::testNeedUpdate));
            add(testCase(&AlgorithmRTCTestSuite::testGetSet));
            add(testCase(&AlgorithmRTCTestSuite::testInitTime));
            add(testCase(&AlgorithmRTCTestSuite::testports));

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
            libpipe::utilities::Parameters p;
            a->setParameters(p);

            delete a;


        }

        void testInitTime()
        {
            timeval tv;
            libpipe::utilities::set_max(tv.tv_sec);
            libpipe::utilities::set_max(tv.tv_usec);

            shouldEqual(tv, Algorithm::MAX_TIME);

            libpipe::utilities::set_min(tv.tv_sec);
            libpipe::utilities::set_min(tv.tv_usec);
            shouldEqual(tv, Algorithm::MIN_TIME);
#ifndef  _WIN32
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "MyAlgorithm");
            a->initMaxTime();
            a->initMinTime();
            delete a;
#endif
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

#ifdef ENABLE_THREADING
            i->lock();
            input->lock();
#endif
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
#ifdef ENABLE_THREADING
            i->unlock();
            input->unlock();
#endif
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

