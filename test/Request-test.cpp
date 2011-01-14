/*
 * Request-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"

#include <libpipe/pipeline/Request.hpp>

#include <sstream>
#include <vector>
#include <string>

using namespace libpipe;

/** Test the Request class.
 */
struct RequestTestSuite : vigra::test_suite {

    /** Constructor.
     * The RequestTestSuite constructor adds all Request tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    RequestTestSuite() : vigra::test_suite("Request") {
        add(testCase(&RequestTestSuite::testConstruction));
        add(testCase(&RequestTestSuite::testIs));
        add(testCase(&RequestTestSuite::testTraceFlag));
        add(testCase(&RequestTestSuite::testTrace));
        //add(testCase(&RequestTestSuite::fail));
    }


    /** Check request construction.
     */
    void testConstruction() {
        // make sure this compiles
        Request req(Request::UPDATE);
        // attempt to construct with an invalid value
        bool thrown = false;
        try {
            Request req(Request::nTypes);
        } catch (Exception& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);
    }

    /** Check Request.is().
     */
    void testIs() {
        Request req(Request::UPDATE);
        shouldEqual(req.is(Request::nTypes), false);
        shouldEqual(req.is(Request::UPDATE), true);
    }

    /** Check trace flag getter/setter
     */
    void testTraceFlag() {
        {
            // getset test
            Request req(Request::UPDATE);
            req.setTraceFlag(req.getTraceFlag());
        }
        Request req(Request::UPDATE);
        // should be initialized to false
        shouldEqual(req.getTraceFlag(), false);
        req.setTraceFlag(true);
        shouldEqual(req.getTraceFlag(), true);
        req.setTraceFlag(false);
        shouldEqual(req.getTraceFlag(), false);
    }

    /** Check trace info handling.
     */
    void testTrace() {
        Request req(Request::UPDATE);
        std::vector<std::string> trace;
        // make sure we initially have an empty trace
        req.getTrace(trace);
        shouldEqual(trace.size(), static_cast<size_t>(0));
        trace.clear();
        // add a message and check the size and content again
        std::string message("Some message.");
        req.addTrace(message);
        req.getTrace(trace);
        shouldEqual(trace.size(), static_cast<size_t>(1));
        shouldEqual(trace[0], message);
        trace.clear();
        // clear the trace info from the request object
        req.clearTrace();
        req.getTrace(trace);
        shouldEqual(trace.size(), static_cast<size_t>(0));
        trace.clear();
        // make sure the traces are sorted
        std::vector<std::string> control;
        for (size_t i = 0; i < 10; ++i) {
            std::ostringstream oss;
            oss << "message no " << i;
            req.addTrace(oss.str());
            control.push_back(oss.str());
        }
        req.getTrace(trace);
        for (size_t i = 0; i < 10; ++i) {
            shouldEqual(trace[i], control[i]);
        }
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Request class has tests.
     */
    void fail() {
        failTest("No unit tests for class Request!");
    }
};


/** The main function that runs the tests for class Request.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    RequestTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

