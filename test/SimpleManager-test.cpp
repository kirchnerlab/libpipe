/*
 * SimpleManager-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#include <exception>
#include <stdexcept>
#include <vector>
#include <string>

#include <libpipe/algorithm/Algorithm.hpp>
#include <libpipe/pipeline/BasicFilter.hpp>
#include <libpipe/pipeline/Request.hpp>
#include <libpipe/pipeline/RequestException.hpp>
#include <libpipe/pipeline/SimpleManager.hpp>

using namespace libpipe;

/** Test suite for the simple manager.
 */
struct SimpleManagerTestSuite : vigra::test_suite {
    /** Constructor.
     * The SimpleManagerTestSuite constructor adds all SimpleManager tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    SimpleManagerTestSuite() : vigra::test_suite("SimpleManager") {
        add(testCase(&SimpleManagerTestSuite::testSetAlgorithm));
        add(testCase(&SimpleManagerTestSuite::testConnect));
        add(testCase(&SimpleManagerTestSuite::testProcessRequestNoAlgorithmSetup));
        add(testCase(&SimpleManagerTestSuite::testProcessRequestNoSources));
        add(testCase(&SimpleManagerTestSuite::testProcessRequestFailingSources));
    }
    
    /** An algorithm that does not change its input.
     */
    class Identity : public Algorithm
    {
      public:
        Identity() : Algorithm(), in_(0), out_(0) {}
        ~Identity() {}
        Request& update(Request& req) {
            LIBPIPE_REQUEST_TRACE(req, "Identity: copying value.");
            out_ = in_;
            this->updateMTime();
            return req;
        }
        int getOutput() { return out_; }
        void setInput(int input) {
            if (in_ != input) {
                in_ = input;
                this->updateMTime();
            }
        }

      private:
        int in_, out_;
    };

    /** An algorithm that throws an exception during execution.
     */
    class RaiseExceptionAlg : public Algorithm
    {
      public:
        RaiseExceptionAlg() : Algorithm() {}
        ~RaiseExceptionAlg() {}
        Request& update(Request& req) {
            // deliberately raise a non-libpipe exception
            throw std::exception();
        }
    };

    /** Derive from Manager to be able to access the protected classes
     * for testing.
     */
    class TestManager : public SimpleManager {
      public:
        Algorithm* getAlgorithm() { return algorithm_; }
        std::set<Filter*> getSources() { return sources_; }
    };
    
    /** Setting the algorithm.
     */
    void testSetAlgorithm() {
        Algorithm* a = new Identity;
        TestManager tm;
        tm.setAlgorithm(a);
        // make sure the pointers point at the same location
        shouldEqual(tm.getAlgorithm(), a);
        delete a;
    }

    /** Test source setup, i.e. connecting.
     */
    void testConnect() {
        TestManager tm;
        shouldEqual(tm.getSources().size(), static_cast<size_t>(0));

        typedef BasicFilter<Identity, TestManager> IdentityFilter;
        Filter* fi = new IdentityFilter("Filter 1: ID");
        tm.connect(fi);
        shouldEqual(tm.getSources().size(), static_cast<size_t>(1));
         
        typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
        Filter* ff = new FailFilter("Filter 2: FAILER");
        tm.connect(ff);
        shouldEqual(tm.getSources().size(), static_cast<size_t>(2));

        delete fi;
        delete ff;
    }

    /** Request processing w/o a defined algorithm.
     */
    void testProcessRequestNoAlgorithmSetup() {
        // make sure we fail if there is no algorithm setup
        TestManager tm;
        Request req(Request::UPDATE);
        bool thrown = false;
        // FIXME: we should have different error classes to distinguish
        //        between different errors.
        try {
            req = tm.processRequest(req);
        } catch (RequestException& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);
    }

    /** Request processing with no sources and a succesful algorithm.
     */
    void testProcessRequestNoSources() {
        TestManager tm;
        Request req(Request::UPDATE);
        req.setTraceFlag(true);
        // the following algorithm should not throw any exceptions
        Identity* a = new Identity;
        tm.setAlgorithm(a);
        shouldEqual(tm.getSources().size(), static_cast<size_t>(0));
        a->setInput(42);
        req = tm.processRequest(req);
        shouldEqual(a->getOutput(), 42);
        delete a;
        std::vector<std::string> trace;
        req.getTrace(trace);
        shouldEqual(trace.size(), static_cast<size_t>(1));
        // now let the algorithm throw an exception
        RaiseExceptionAlg* b = new RaiseExceptionAlg;
        tm.setAlgorithm(b);
        bool thrown = false;
        try {
            req = tm.processRequest(req);
        } catch (RequestException& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);
        delete b;
    }

    /** Request processing if one of the sources fails.
     */
    void testProcessRequestFailingSources() {
        TestManager tm;
        Request req(Request::UPDATE);
        Algorithm* a = new Identity;
        tm.setAlgorithm(a);

        typedef BasicFilter<Identity, TestManager> IdentityFilter;
        IdentityFilter* fi = new IdentityFilter("Id");
        tm.connect(fi);

        // this is the ok source
        fi->getAlgorithm()->setInput(42);
        req = tm.processRequest(req);
        shouldEqual(fi->getAlgorithm()->getOutput(), 42);

        // now add the failing source
        typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
        FailFilter* ff = new FailFilter("FailFilter");
        tm.connect(ff);
        
        bool thrown = false;
        try {
            req = tm.processRequest(req);
        } catch (RequestException& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);

        delete ff;
        delete fi;
        delete a;
    } 

    /** Test that is guaranteed to fail.
     * Leave this in until the complete SimpleManager class has tests.
     */
};


/** The main function that runs the tests for class SimpleManager.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    SimpleManagerTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

