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

#include "libpipe/rtc/Config.hpp"



/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct ConfigTestSuite : vigra::test_suite {
    /** Constructor.
     * The rtc/LibpipeConfigTestSuite constructor adds all rtc/LibpipeConfig tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ConfigTestSuite() : vigra::test_suite("rtc/LibpipeConfig") {
        add(testCase(&ConfigTestSuite::structComparison));
    }



    void structComparison(){
        libpipe::rtc::PipelineDescription s1;
        libpipe::rtc::PipelineDescription s2;

        s1.requestRank = 2;
        s2.requestRank = 3;

        libpipe::rtc::PipelineDescriptionLess compFct;

        shouldEqual(compFct(s1,s2), true);
        shouldEqual(compFct(s2,s1), false);




    }
};


/** The main function that runs the tests for class rtc/LibpipeConfig.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ConfigTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

