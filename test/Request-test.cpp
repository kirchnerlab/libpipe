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

#include <libpipe/Request.hpp>

#include <sstream>
#include <vector>
#include <string>

using namespace libpipe;

/** Test the Request class.
 */
struct RequestTestSuite : vigra::test_suite
{

    /** Constructor.
     * The RequestTestSuite constructor adds all Request tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    RequestTestSuite() :
        vigra::test_suite("Request")
    {
        add(testCase(&RequestTestSuite::testConstruction));
        add(testCase(&RequestTestSuite::testIs));
        add(testCase(&RequestTestSuite::testTraceFlag));
        add(testCase(&RequestTestSuite::testTrace));
        //add(testCase(&RequestTestSuite::fail));
    }

    /** Check request construction.
     */
    void testConstruction()
    {
        // make sure this compiles
        Request reqU(Request::UPDATE);
        Request reqD(Request::DELETE);
    }

    /** Check Request.is().
     */
    void testIs()
    {
        Request reqU(Request::UPDATE);
        shouldEqual(reqU.is(Request::UPDATE), true);

        Request reqD(Request::DELETE);
        shouldEqual(reqD.is(Request::DELETE),true);

        shouldEqual(reqU.is(Request::DELETE), false);
        shouldEqual(reqD.is(Request::UPDATE), false);
    }

    /** Check trace flag getter/setter
     */
    void testTraceFlag()
    {
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
    void testTrace()
    {
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
        // do not compare the date/time part.
        shouldEqual(trace[0].substr(trace[0].size()-message.size(),
                        message.size()), message);
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
            shouldEqual(trace[i].substr(trace[i].size()-control[i].size(),
                            control[i].size()), control[i]);
        }
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

