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
#ifndef  _WIN32
    #define private public
    #define protected public
#endif
#include "libpipe/ctc/Algorithm.hpp"
#ifndef  _WIN32
    #undef private
    #undef protected
#endif
#include <libpipe/utilities/Time.hpp> // for gettimeofday
using namespace libpipe::ctc;


/** Test suite for the libpipe::Algorithm base class.
 * The basic setup is: derive from Algorithm and test all inherited functions. 
 */
struct AlgorithmTestSuite : vigra::test_suite
{

    /** A local class that derives from Algorithm.
     */
    class MyAlgorithm : public Algorithm
    {
    public:
        MyAlgorithm() :
            Algorithm()
        {
        }
        ~MyAlgorithm()
        {
        }
        virtual void update(libpipe::Request& req)
        {
            // dummy
        }
    };

    /** Constructor.
     * The AlgorithmTestSuite constructor adds all Algorithm tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    AlgorithmTestSuite() :
        vigra::test_suite("Algorithm")
    {
        add(testCase(&AlgorithmTestSuite::testInitialization));
        add(testCase(&AlgorithmTestSuite::testProcessRequest));
        add(testCase(&AlgorithmTestSuite::testUpdateMTime));
        add(testCase(&AlgorithmTestSuite::testNeedUpdate));
        add(testCase(&AlgorithmTestSuite::testGetSet));
        add(testCase(&AlgorithmTestSuite::testInitTime));
    }



    /** Test if the max initialization worked.
     */
    void testInitialization()
    {
        MyAlgorithm a;
        shouldEqual(a.getMTime(), Algorithm::MAX_TIME);
    }

    /** Test Algorithm::processRequest.
     */
    void testProcessRequest(){
        MyAlgorithm a;
        libpipe::Request req(libpipe::Request::DELETE);
        a.processRequest(req);
        shouldEqual(a.getMTime(), Algorithm::MIN_TIME);

    }

    /** Test Algorithm::updateMTime().
     */
    void testUpdateMTime()
    {
        // check if the self-update works.
        MyAlgorithm a;
        shouldEqual(a.needUpdate(), true);
        a.updateMTime();
        shouldEqual(a.needUpdate(), false);
    }

    /** Test Algorithm::needUpdate().
     */
    void testNeedUpdate()
    {
        MyAlgorithm a;
        // we expect the need for an update right after construction
        shouldEqual(a.needUpdate(), true);
        // now set the time to now()
        timeval tv;
        gettimeofday(&tv, NULL);
        a.setMTime(tv);
        shouldEqual(a.needUpdate(), false);
    }

    /** Run GET/SET tests for all member variables.
     */
    void testGetSet()
    {
        MyAlgorithm a;
        a.setMTime(a.getMTime());
    }


    void testInitTime()
    {
        timeval tv;
        libpipe::utilities::set_max(tv.tv_sec);
        libpipe::utilities::set_max(tv.tv_usec);
        shouldEqual(tv,Algorithm::MAX_TIME);

        libpipe::utilities::set_min(tv.tv_sec);
        libpipe::utilities::set_min(tv.tv_usec);
        shouldEqual(tv,Algorithm::MIN_TIME);
        MyAlgorithm a;
#ifndef  _WIN32
        a.initMaxTime();
        a.initMinTime();
#endif
    }

};

/** The main function that runs the tests for class Algorithm.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    AlgorithmTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

