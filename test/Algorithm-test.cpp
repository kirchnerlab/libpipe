/*
 * Algorithm-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner.
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#include "libpipe/Algorithm.hpp"
#include <sys/time.h> // for gettimeofday
using namespace libpipe;

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
        virtual Request& update(Request& req)
        {
            // dummy
            return req;
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
        // add(testCase(&AlgorithmTestSuite::fail));
        add(testCase(&AlgorithmTestSuite::testFreeOperators));
        add(testCase(&AlgorithmTestSuite::testInitialization));
        add(testCase(&AlgorithmTestSuite::testUpdateMTime));
        add(testCase(&AlgorithmTestSuite::testNeedUpdate));
        add(testCase(&AlgorithmTestSuite::testGetSet));
    }

    /** Test free operators
     */
    void testFreeOperators()
    {
        timeval tv1, tv2;
        gettimeofday(&tv1, NULL);
        tv2 = tv1;
        shouldEqual(operator==(tv1, tv2), true);
        shouldEqual(operator==(tv2, tv1), true);
        shouldEqual(operator<=(tv1, tv2), true);
        shouldEqual(operator<=(tv2, tv1), true);
        tv2.tv_sec += 1;
        shouldEqual(operator==(tv1, tv2), false);
        shouldEqual(operator==(tv2, tv1), false);
        shouldEqual(operator<=(tv1, tv2), true);
        shouldEqual(operator<=(tv2, tv1), false);
        tv2 = Algorithm::MAX_TIME;
        shouldEqual(operator==(tv1, tv2), false);
        shouldEqual(operator==(tv2, tv1), false);
        shouldEqual(operator<=(tv1, tv2), true);
        shouldEqual(operator<=(tv2, tv1), false);
        tv1 = Algorithm::MAX_TIME;
        shouldEqual(operator==(tv1, tv2), true);
        shouldEqual(operator==(tv2, tv1), true);
        shouldEqual(operator<=(tv1, tv2), true);
        shouldEqual(operator<=(tv2, tv1), true);
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
        timeval tv;
        gettimeofday(&tv, NULL);
        a.setMTime(tv);
        shouldEqual(a.getMTime(),tv);

    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Algorithm class has tests.
     */
    void fail()
    {
        failTest("No unit tests for class Algorithm!");
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

