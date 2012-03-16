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

#include <libpipe/ctc/SharedData.hpp>

using namespace libpipe::ctc;

/** Test suite for the SharedData template class
 */
struct SharedDataTestSuite : vigra::test_suite
{
    /** Constructor.
     * The SharedDataTestSuite constructor adds all SharedData tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    SharedDataTestSuite() :
        vigra::test_suite("SharedData")
    {
        add(testCase(&SharedDataTestSuite::instance));
    }

    void instance()
    {
        SharedData<int> s;
        shouldEqual(s.isNull(), true);
        SharedData<int> s2(new int);
        shouldEqual(s2.isNull(), false);
        *(s2.get()) = 10;
        int* pI = new int(5);
        s.set(pI);
        shouldEqual(s.get(), pI);
        shouldEqual(*(s.get()), 5);
    }
};

/** The main function that runs the tests for class SharedData.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    SharedDataTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

