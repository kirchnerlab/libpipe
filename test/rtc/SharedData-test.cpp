/*
 * SharedData-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */
#include <libpipe/config.hpp>

#include <iostream>
#include "vigra/unittest.hxx"

#include <libpipe/SharedData.hpp>

using namespace libpipe;

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
        vigra::test_suite("rtc/SharedData")
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

