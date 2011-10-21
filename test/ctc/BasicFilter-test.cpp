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
#include <libpipe/ctc/Algorithm.hpp>
#include <libpipe/ctc/BasicFilter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/ctc/Manager.hpp>

#include "ctc/utils.hpp"

using namespace libpipe::ctc;

/** Test routines for the BasicFilter template class.
 */
struct BasicFilterTestSuite : vigra::test_suite
{
    /** Constructor.
     * The BasicFilterTestSuite constructor adds all BasicFilter tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    BasicFilterTestSuite() :
        vigra::test_suite("BasicFilter")
    {
        add(testCase(&BasicFilterTestSuite::testAlgorithm));
        add(testCase(&BasicFilterTestSuite::testManager));
    }

    /** Derived class with exposed setters.
     */
    typedef BasicFilter<RaiseExceptionAlg, TestManager> F;
    class TestFilter : public F
    {
    public:
        TestFilter(const std::string& name) :
            F(name)
        {
        }
        virtual ~TestFilter()
        {
        }
        void setAlgorithm(Algorithm* a)
        {
            F::setAlgorithm(a);
        }
        void setManager(Manager* m)
        {
            F::setManager(m);
        }
    };

    void testAlgorithm()
    {
        // getset
        TestFilter* f = new TestFilter("foo");
        RaiseExceptionAlg* p = f->getAlgorithm();
        f->setAlgorithm(f->getAlgorithm());
        shouldEqual(f->getAlgorithm(), p);
        // switch algorithm
        p = new RaiseExceptionAlg();
        // the filter takes possession of the algorithm
        f->setAlgorithm(p);
        //shouldEqual(f->getAlgorithm(), p);
        delete f;
    }

    void testManager()
    {
        // getset
        TestFilter* f = new TestFilter("bar");
        TestManager* p = f->getManager();
        f->setManager(f->getManager());
        shouldEqual(f->getManager(), p);
        // switch manager
        p = new TestManager;
        // the filter takes possession of the manager
        f->setManager(p);
        shouldEqual(f->getManager(), p);
        delete f;
    }

};

/** The main function that runs the tests for class BasicFilter.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    BasicFilterTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

