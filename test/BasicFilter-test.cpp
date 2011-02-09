/*
 * BasicFilter-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#include <libpipe/Algorithm.hpp>
#include <libpipe/BasicFilter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/Manager.hpp>

#include "utils.hpp"

using namespace libpipe;


/** Test routines for the BasicFilter template class.
 */
struct BasicFilterTestSuite : vigra::test_suite {
    /** Constructor.
     * The BasicFilterTestSuite constructor adds all BasicFilter tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    BasicFilterTestSuite() : vigra::test_suite("BasicFilter") {
        add(testCase(&BasicFilterTestSuite::testAlgorithm));
        add(testCase(&BasicFilterTestSuite::testManager));
    }

    /** Derived class with exposed setters.
     */
    typedef BasicFilter<RaiseExceptionAlg, TestManager> F;
    class TestFilter : public F {
      public:
        TestFilter(const std::string& name) : F(name) {}
        virtual ~TestFilter() {}
        void setAlgorithm(Algorithm* a) { F::setAlgorithm(a); }
        void setManager(Manager* m) { F::setManager(m); }
    };

    void testAlgorithm() {
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

    void testManager() {
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

