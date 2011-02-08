/*
 * Filter-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#include <libpipe/algorithm/Algorithm.hpp>
#include <libpipe/pipeline/BasicFilter.hpp>
#include <libpipe/pipeline/Request.hpp>
#include <libpipe/pipeline/RequestException.hpp>
#include <libpipe/pipeline/Manager.hpp>

#include "utils.hpp"

using namespace libpipe;


/** Test for the Filter base class.
 * Derives from the Filter base class and tests the standard implementations. 
 */
struct FilterTestSuite : vigra::test_suite {
    /** Constructor.
     * The FilterTestSuite constructor adds all Filter tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    FilterTestSuite() : vigra::test_suite("Filter") {
        add(testCase(&FilterTestSuite::testConstructionAndDestruction));
        add(testCase(&FilterTestSuite::testCallChain));
        add(testCase(&FilterTestSuite::testName));
        add(testCase(&FilterTestSuite::testAlgorithm));
        add(testCase(&FilterTestSuite::testManager));
    }

    void testConstructionAndDestruction() {
        // this is a test for valgrind
        typedef BasicFilter<Identity, TestManager> IdentityFilter;
        IdentityFilter filter("bla");
    }

    void testCallChain() {
        // tests if the filter calls its managers process request function
        // the manager will then call the process request function of the fail
        // filter and raise an exception.
        typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
        Filter* f = new FailFilter("Fail!");
        Request req(Request::UPDATE);
        bool thrown = false;
        try {
            req = f->processRequest(req);
        } catch (RequestException& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);
        delete f;
    }

    void testName() {
        // getset name
        typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
        Filter* f = new FailFilter("Fail!");
        f->setName(f->getName());
        shouldEqual(strncmp(f->getName().c_str(), "Fail!", 5), 0);
        f->setName("foo");
        shouldEqual(strncmp(f->getName().c_str(), "foo", 3), 0);
        delete f;
    }

    typedef BasicFilter<RaiseExceptionAlg, TestManager> F;
    class TestFilter : public F {
      public:
        TestFilter(const std::string& name) : F(name) {}
        virtual ~TestFilter() {}
        void setAlgorithm(RaiseExceptionAlg* a) { F::setAlgorithm(a); }
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
        shouldEqual(f->getAlgorithm(), p);
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

