/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2011 Marc Kirchner
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

#include <iostream>
#include "vigra/unittest.hxx"
#include <exception>
#include <stdexcept>
#include <vector>
#include <string>

#include <libpipe/ctc/Algorithm.hpp>
#include <libpipe/ctc/BasicFilter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/ctc/Manager.hpp>
#include <libpipe/ctc/Pipeline.hpp>

#include <boost/pointer_cast.hpp>

#include "ctc/utils.hpp"

using namespace libpipe::ctc;

/** Test suite for the simple manager.
 */
struct ManagerTestSuite : vigra::test_suite
{
        /** Constructor.
         * The ManagerTestSuite constructor adds all Manager tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        ManagerTestSuite() :
                vigra::test_suite("Manager")
        {
            add(testCase(&ManagerTestSuite::testSetAlgorithm));
            add(testCase(&ManagerTestSuite::testSharedPtr));
            add(testCase(&ManagerTestSuite::testConnect));
            add(
                testCase(&ManagerTestSuite::testProcessRequestNoAlgorithmSetup));
            add(testCase(&ManagerTestSuite::testProcessRequestNoSources));
            add(testCase(&ManagerTestSuite::testProcessRequestFailingSources));
            add(testCase(&ManagerTestSuite::testProcessRequestFailingSourcesDelete));

        }

        /** Setting the algorithm.
         */
        void testSetAlgorithm()
        {
            Algorithm* a = new Identity;
            Manager m;
            m.setAlgorithm(a);
            // make sure the pointers point at the same location
            shouldEqual(m.getAlgorithm(), a);
            delete a;
        }

        /** Test shared_ptr
         */
        void testSharedPtr()
        {
            typedef BasicFilter<Identity, TestManager> IdentityFilter;
            boost::shared_ptr<Filter> fi(new IdentityFilter("Filter 1: ID"));
            shouldEqual(fi.use_count(), 1);
            shouldEqual(fi.unique(), true);

            typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
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
            TestManager tm;
            shouldEqual(tm.getSources().size(), static_cast<size_t>(0));

            typedef BasicFilter<Identity, TestManager> IdentityFilter;
            boost::shared_ptr<Filter> fi(new IdentityFilter("Filter 1: ID"));
            tm.connect(fi);
            shouldEqual(tm.getSources().size(), static_cast<size_t>(1));

            typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
            boost::shared_ptr<Filter> ff(new FailFilter("Filter 2: FAILER"));
            tm.connect(ff);
            shouldEqual(tm.getSources().size(), static_cast<size_t>(2));

        }

        /** Request processing w/o a defined algorithm.
         */
        void testProcessRequestNoAlgorithmSetup()
        {
            // make sure we fail if there is no algorithm setup
            TestManager tm;
            libpipe::Request req(libpipe::Request::UPDATE);
            bool thrown = false;
            // FIXME: we should have different error classes to distinguish
            //        between different errors.
            try {
                req = tm.processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }
            shouldEqual(thrown, true);
        }

        /** Request processing with no sources and a successful algorithm.
         */
        void testProcessRequestNoSources()
        {
            TestManager tm;
            libpipe::Request req(libpipe::Request::UPDATE);
            libpipe::ctc::Pipeline pipeline;
            pipeline.setTraceFlag(true);
            // the following algorithm should not throw any exceptions
            Identity* a = new Identity;
            tm.setAlgorithm(a);
            shouldEqual(tm.getSources().size(), static_cast<size_t>(0));
            a->setInput(42);
            req = tm.processRequest(req);
            shouldEqual(a->getOutput(), 42);
            delete a;
            std::vector<std::string> trace;
            trace=pipeline.getTrace();
            shouldEqual(trace.size(), static_cast<size_t>(1));
            // now let the algorithm throw an exception
            RaiseExceptionAlg* b = new RaiseExceptionAlg;
            tm.setAlgorithm(b);
            bool thrown = false;
            try {
                req = tm.processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);
            delete b;
        }

        /** Request processing if one of the sources fails.
         */
        void testProcessRequestFailingSources()
        {
            TestManager tm;
            libpipe::Request req(libpipe::Request::UPDATE);
            Algorithm* a = new Identity;
            tm.setAlgorithm(a);

            typedef BasicFilter<Identity, TestManager> IdentityFilter;
            boost::shared_ptr<IdentityFilter> fi(new IdentityFilter("Id"));
            tm.connect(boost::dynamic_pointer_cast<Filter>(fi));

            // this is the ok source
            fi->getAlgorithm()->setInput(42);
            req = tm.processRequest(req);
            shouldEqual(fi->getAlgorithm()->getOutput(), 42);

            // now add the failing source
            typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
            boost::shared_ptr<Filter> ff(new FailFilter("FailFilter"));
            tm.connect(ff);

            bool thrown = false;
            try {
                req = tm.processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);

            delete a;
        }
        /** Request processing if the request type is delete.
         */
        void testProcessRequestFailingSourcesDelete()
        {
            TestManager tm;
            libpipe::Request req(libpipe::Request::DELETE);
            Algorithm* a = new Identity;
            tm.setAlgorithm(a);

            typedef BasicFilter<Identity, TestManager> IdentityFilter;
            boost::shared_ptr<IdentityFilter> fi(new IdentityFilter("Id"));
            tm.connect(boost::dynamic_pointer_cast<Filter>(fi));

            // make sure that the filters are deleted
            fi->getAlgorithm()->setInput(42);
            shouldEqual(tm.getSources().size(), static_cast<size_t>(1));
            req = tm.processRequest(req);
            shouldEqual(tm.getSources().size(), static_cast<size_t>(0));
            shouldEqual(tm.getAlgorithm()->needUpdate(), false);


            delete a;
        }

        /** Test that is guaranteed to fail.
         * Leave this in until the complete Manager class has tests.
         */
};

/** The main function that runs the tests for class Manager.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ManagerTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

