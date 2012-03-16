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
#include <libpipe/config.hpp>
#include <iostream>
#include "vigra/unittest.hxx"
#include <cstring>
#include <string>
#include <libpipe/utilities/Exception.hpp>

using namespace libpipe::utilities;

/** Test suite for the Exception class.
 */
struct ExceptionTestSuite : vigra::test_suite
{
    /** Constructor.
     * The ExceptionTestSuite constructor adds all Exception tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ExceptionTestSuite() :
        vigra::test_suite("Exception")
    {
        add(testCase(&ExceptionTestSuite::testDerivedClass));
        add(testCase(&ExceptionTestSuite::testConstruction));
        add(testCase(&ExceptionTestSuite::testMacros));
        // add(testCase(&ExceptionTestSuite::fail));
    }

    /** Make sure we can derive from it.
     */
    class TestException : public Exception
    {
    public:
        TestException() :
            Exception("qwerty")
        {
        }
    };

    class TestExceptionWithOverload : public Exception
    {
    public:
        TestExceptionWithOverload() :
            Exception("qwerty")
        {
        }
        virtual const char * what(void)
        {
            return Exception::what();
        }
    };

    /** Try to instantiate a derived class.
     */
    void testDerivedClass()
    {
        TestException t;
        shouldEqual(strncmp(t.what(), "qwerty", 6), 0);
        TestExceptionWithOverload to;
        shouldEqual(strncmp(to.what(), "qwerty", 6), 0);
    }

    /** Test construction.
     */
    void testConstruction()
    {
        Exception e("message");
        shouldEqual(strncmp("message", e.what(), 7), 0);
        Exception e2(std::string("message"));
        shouldEqual(strncmp("message", e2.what(), 7), 0);
    }

    /** Test the macros that come with the class.
     */
    void testMacros()
    {
        // also test the macros
        bool thrown = false;
        try {
            libpipe_fail("abc");
        } catch (Exception& e) {
            shouldEqual(strncmp("abc", e.what(), 3), 0);
            thrown = true;
        }
        shouldEqual(thrown, true);
        thrown = false;
        std::string abc("abc");
        try {
            libpipe_fail(abc);
        } catch (Exception& e) {
            shouldEqual(strncmp("abc", e.what(), 3), 0);
            thrown = true;
        }
        shouldEqual(thrown, true);
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Exception class has tests.
     */
    void fail()
    {
        failTest("No unit tests for class Exception!");
    }
};

/** The main function that runs the tests for class Exception.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ExceptionTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

