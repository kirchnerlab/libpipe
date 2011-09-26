/*
 * Filter-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <iostream>
#include <cstring>
#include "vigra/unittest.hxx"
#include <libpipe/Algorithm.hpp>
#include <libpipe/BasicFilter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/Manager.hpp>

#include "utils.hpp"

using namespace libpipe;

/** Test for the Filter base class.
 * Derives from the Filter base class and tests the standard implementations. 
 */
struct FilterTestSuite : vigra::test_suite
{
        /** Constructor.
         * The FilterTestSuite constructor adds all Filter tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        FilterTestSuite() :
                vigra::test_suite("Filter")
        {
            add(testCase(&FilterTestSuite::testConstructionAndDestruction));
            add(testCase(&FilterTestSuite::testCallChain));
            add(testCase(&FilterTestSuite::testName));
        }

        void testConstructionAndDestruction()
        {
            // this is a test for valgrind
            typedef BasicFilter<Identity, TestManager> IdentityFilter;
            IdentityFilter filter("bla");
        }

        void testCallChain()
        {
            // tests if the filter calls its managers process request function
            // the manager will then call the process request function of the fail
            // filter and raise an exception.
            typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
            Filter* f = new FailFilter("Fail!");
            Request req(Request::UPDATE);
            bool thrown = false;
            try {
                req = f->processRequest(req);
            } catch (RequestException& e) {
                thrown = true;
            }
            shouldEqual(thrown, true);

            Request req1(Request::DELETE);
            thrown = false;
            try {
                req1 = f->processRequest(req1);
            } catch (RequestException& e) {
                thrown = true;
            }
            shouldEqual(thrown, false);

            Request req2(Request::Type(3));
            thrown = false;
            try {
                req2 = f->processRequest(req2);
            } catch (RequestException& e) {
                thrown = true;
            }
            shouldEqual(thrown, true);

            delete f;
        }

        void testName()
        {
            // getset name
            typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
            Filter* f = new FailFilter("Fail!");
            f->setName(f->getName());
            shouldEqual(strncmp(f->getName().c_str(), "Fail!", 5), 0);
            f->setName("foo");
            shouldEqual(strncmp(f->getName().c_str(), "foo", 3), 0);
            delete f;
        }

        /*
         * tests for get/setAlgorithm and get/setManager are part
         * of the BasicFilter<A, M> test routines.
         */

};

/** The main function that runs the tests for class Filter.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    FilterTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

