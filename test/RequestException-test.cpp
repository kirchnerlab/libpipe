/*
 * RequestException-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */
#include <libpipe/config.hpp>

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

