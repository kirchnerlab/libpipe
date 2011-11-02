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

#define private public
#define protected public
#include <libpipe/rtc/Manager.hpp>
#undef private
#undef protected
#include <iostream>
#include "vigra/unittest.hxx"
#include <exception>
#include <stdexcept>
#include <vector>
#include <string>

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Filter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>

#include <libpipe/rtc/ManagerFactory.hpp>

#include <boost/pointer_cast.hpp>

#include "rtc/utils.hpp"

using namespace libpipe::rtc;
/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct ManagerRTCTestSuite : vigra::test_suite
{
        /** Constructor.
         * The ManagerRTCTestSuite constructor adds all ManagerRTC tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        ManagerRTCTestSuite() :
                vigra::test_suite("rtc/Manager")
        {
            add(testCase(&ManagerRTCTestSuite::testSetAlgorithm));
            add(testCase(&ManagerRTCTestSuite::testSharedPtr));
            add(testCase(&ManagerRTCTestSuite::testConnect));
            add(
                testCase(&ManagerRTCTestSuite::testProcessRequestNoAlgorithmSetup));
            add(testCase(&ManagerRTCTestSuite::testProcessRequestNoSources));
            add(
                testCase(&ManagerRTCTestSuite::testProcessRequestFailingSources));
            add(
                testCase(&ManagerRTCTestSuite::testProcessRequestFailingSourcesDelete));
        }

        /** Setting the algorithm.
         */
        void testSetAlgorithm()
        {
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "IdentityRTC");
            Manager* m = ManagerFactory::instance().createObject("MangerRTC");
            m->setAlgorithm(a);
            std::cout << m->getAlgorithm() << "b" << a << std::endl;
            // make sure the pointers point at the same location
            shouldEqual(m->getAlgorithm(), a);
            delete a;
            delete m;

        }

        /** Test shared_ptr
         */
        void testSharedPtr()
        {
            boost::shared_ptr<Filter> fi(
                Filter::create("Filter 1: ID", "IdentityRTC", "MangerRTC"));
            shouldEqual(fi.use_count(), 1);
            shouldEqual(fi.unique(), true);

            boost::shared_ptr<Filter> ff(fi);

            shouldEqual(fi.use_count(), 2);
            shouldEqual(fi.unique(), false);
            shouldEqual(ff, fi);

            fi.reset();
            shouldEqual(fi.use_count(), 0);
            shouldEqual(ff.use_count(), 1);
            shouldEqual(ff.unique(), true);

        }

        /** Test source setup, i.e. connecting.
         */
        void testConnect()
        {
            // Use a derived class to gain access to the source list.
            Manager* tm = ManagerFactory::instance().createObject("MangerRTC");
            shouldEqual(tm->getSources().size(), static_cast<size_t>(0));

            boost::shared_ptr<Filter> fi(
                Filter::create("Filter 1: ID", "IdentityRTC", "MangerRTC"));

            tm->connect(fi);
            shouldEqual(tm->getSources().size(), static_cast<size_t>(1));

            boost::shared_ptr<Filter> ff(
                Filter::create("Filter 2: FAILER", "RaiseExceptionAlg",
                    "MangerRTC"));

            tm->connect(ff);
            shouldEqual(tm->getSources().size(), static_cast<size_t>(2));
            delete tm;

        }

        /** Request processing w/o a defined algorithm.
         */
        void testProcessRequestNoAlgorithmSetup()
        {
            // make sure we fail if there is no algorithm setup
            Manager* tm = ManagerFactory::instance().createObject("MangerRTC");
            libpipe::Request req(libpipe::Request::UPDATE);
            bool thrown = false;
            // FIXME: we should have different error classes to distinguish
            //        between different errors.
            try {
                tm->processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);
            delete tm;

        }

        /** Request processing with no sources and a successful algorithm.
         */
        void testProcessRequestNoSources()
        {
            Manager* tm = ManagerFactory::instance().createObject("MangerRTC");
            libpipe::Request req(libpipe::Request::UPDATE);
            req.setTraceFlag(true);
            // the following algorithm should not throw any exceptions
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "IdentityRTC");
            tm->setAlgorithm(a);
            shouldEqual(tm->getSources().size(), static_cast<size_t>(0));
            tm->processRequest(req);
            delete a;
            std::vector<std::string> trace;
            req.getTrace(trace);
            shouldEqual(trace.size(), static_cast<size_t>(1));
            // now let the algorithm throw an exception
            Algorithm* b = AlgorithmFactory::instance().createObject(
                "RaiseExceptionAlg");
            tm->setAlgorithm(b);
            bool thrown = false;
            try {
                tm->processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);
            delete b;
            delete tm;

        }

        /** Request processing if one of the sources fails.
         */
        void testProcessRequestFailingSources()
        {
            Manager* tm = ManagerFactory::instance().createObject("MangerRTC");
            libpipe::Request req(libpipe::Request::UPDATE);

            Algorithm* a = AlgorithmFactory::instance().createObject(
                "IdentityRTC");
            tm->setAlgorithm(a);

            boost::shared_ptr<Filter> fi(
                Filter::create("Id", "IdentityRTC", "MangerRTC"));
            fi->getManager()->setAlgorithm(a);

            tm->connect(boost::dynamic_pointer_cast<Filter>(fi));

            // this is the ok source

            tm->processRequest(req);

            // now add the failing source only if not threading is enabled
            boost::shared_ptr<Filter> ff(
                Filter::create("FailFilter", "RaiseExceptionAlg",
                    "MangerRTC"));
            bool thrown;
            thrown = false;

#ifndef ENABLE_THREADING

            tm->connect(ff);

            try {
                tm->processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);

            tm->connect(ff);

            thrown = false;
            try {
                tm->processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);
#endif

            delete a;
            delete tm;

        }
        /** Request processing if the request type is delete.
         */
        void testProcessRequestFailingSourcesDelete()
        {
            Manager* tm = ManagerFactory::instance().createObject("MangerRTC");
            libpipe::Request req(libpipe::Request::DELETE);
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "IdentityRTC");
            tm->setAlgorithm(a);

            boost::shared_ptr<Filter> fi(
                Filter::create("Id", "IdentityRTC", "MangerRTC"));

            tm->connect(boost::dynamic_pointer_cast<Filter>(fi));

            // make sure that the filters are deleted
            shouldEqual(tm->getSources().size(), static_cast<size_t>(1));
            tm->processRequest(req);
            shouldEqual(tm->getSources().size(), static_cast<size_t>(0));
            shouldEqual(tm->getAlgorithm()->needUpdate(), false);

            delete a;
            delete tm;
        }
};

/** The main function that runs the tests for class ManagerRTC.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ManagerRTCTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

