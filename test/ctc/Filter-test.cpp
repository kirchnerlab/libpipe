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
#include <cstring>
#include "vigra/unittest.hxx"
#include <libpipe/ctc/Algorithm.hpp>
#include <libpipe/ctc/BasicFilter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/ctc/Manager.hpp>

#include "ctc/utils.hpp"

using namespace libpipe::ctc;

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
        libpipe::Request req(libpipe::Request::UPDATE);
        bool thrown = false;
        try {
            f->processRequest(req);
        } catch (libpipe::RequestException& e) {
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

