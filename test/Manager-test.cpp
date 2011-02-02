/*
 * Manager-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#include <libpipe/pipeline/Manager.hpp>

using namespace libpipe;

/** Test suite for the Manager base class.
 * This is a very simple test, that just makes sure that classes that derive
 * from Manager and overload the correct methods can be instanciated.
 */
struct ManagerTestSuite : vigra::test_suite {
    /** Constructor.
     * The ManagerTestSuite constructor adds all Manager tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ManagerTestSuite() : vigra::test_suite("Manager") {
        add(testCase(&ManagerTestSuite::deriveAndInstanciate));
    }

    /** Class derived from Manager for testing purposes.
     */
    class Derived : public Manager {
      public:
        virtual ~Derived() {}
        virtual Request& processRequest(Request& r) {
            return r;
        }
    };

    /** Try to instanciate the derived class.
     */
    void deriveAndInstanciate(void) {
        Derived d;
        Request r(Request::UPDATE);
        Request s = d.processRequest(r);
        shouldEqual(s.is(Request::UPDATE), true);
    }
};


/** The main function that runs the tests for class Manager.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ManagerTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

