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
#include <cstring>
#include "vigra/unittest.hxx"
#include <libpipe/RequestException.hpp>

using namespace libpipe;

/** Test suite for the RequestException class.
 */
struct RequestExceptionTestSuite : vigra::test_suite
{
    /** Constructor.
     * The RequestExceptionTestSuite constructor adds all RequestException tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    RequestExceptionTestSuite() :
        vigra::test_suite("RequestException")
    {
        add(testCase(&RequestExceptionTestSuite::testConstruction));
        add(testCase(&RequestExceptionTestSuite::testThrowCatch));
    }

    /** Test construction and destruction.
     */
    void testConstruction()
    {
        RequestException re("bla");
        shouldEqual(strncmp(re.what(), "bla", 3), 0);
    }

    /** Test throwing and catching the exception.
     */
    void testThrowCatch()
    {
        bool caught = false;
        try {
            RequestException e("qwerty");
            shouldEqual(strcmp(e.what(), "qwerty"), static_cast<int>(0));
            throw e;
        } catch (RequestException& e) {
            // catch regularly
            shouldEqual(strcmp(e.what(), "qwerty"), static_cast<int>(0));
            caught = true;
        }
        shouldEqual(caught, true);
    }
};

/** The main function that runs the tests for class RequestException.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    RequestExceptionTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

