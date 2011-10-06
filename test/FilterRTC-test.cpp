/*
 * FilterRTC-test.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#include <libpipe/RTC/FilterRTC.hpp>
#include <libpipe/RTC/LibpipeFactories.hpp>

#include <typeinfo>

#include "utilsRTC.hpp"

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct FilterRTCTestSuite : vigra::test_suite
{
        /** Constructor.
         * The BasicFilterRTCTestSuite constructor adds all BasicFilterRTC tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        FilterRTCTestSuite() :
                vigra::test_suite("FilterRTC")
        {
            add(testCase(&FilterRTCTestSuite::testConstructionAndDestruction));
            add(testCase(&FilterRTCTestSuite::testAlgorithm));
            add(testCase(&FilterRTCTestSuite::testManager));
            add(testCase(&FilterRTCTestSuite::testCallChain));
            add(testCase(&FilterRTCTestSuite::testName));
        }

        void testConstructionAndDestruction()
        {

            libpipe::rtc::FilterRTC* bf = libpipe::rtc::FilterRTC::create(
                "filter1", "IdentityRTC", "MangerRTC");
            AlgorithmRTC* iA =
                    libpipe::rtc::AlgorithmFactory::instance().createObject(
                        "IdentityRTC");
            shouldEqual(typeid(iA)==typeid(bf->getAlgorithm()), true);
            delete bf;
            delete iA;
        }

        void testAlgorithm()
        {
            // getset
            libpipe::rtc::FilterRTC* bf = libpipe::rtc::FilterRTC::create(
                "filter1", "RaiseExceptionAlg", "MangerRTC");
            AlgorithmRTC* p = bf->getAlgorithm();
            shouldEqual(bf->getAlgorithm(), p);
            // switch algorithm

            delete bf;

        }

        void testManager()
        {
            // getset
            libpipe::rtc::FilterRTC* bf = libpipe::rtc::FilterRTC::create(
                            "filter1", "RaiseExceptionAlg", "MangerRTC");
            ManagerRTC* p = bf->getManager();
            shouldEqual(bf->getManager(), p);

            delete bf;
        }

        void testCallChain()
        {
            using namespace libpipe::rtc;
            // tests if the filter calls its managers process request function
            // the manager will then call the process request function of the fail
            // filter and raise an exception.
            FilterRTC* f = FilterRTC::create("fail Filter",
                "RaiseExceptionAlg", "MangerRTC");
            libpipe::Request req(libpipe::Request::UPDATE);
            bool thrown = false;
            try {
                req = f->processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);
            delete f;
        }

        void testName()
        {
            // getset name
            using namespace libpipe::rtc;

            //typedef BasicFilter<RaiseExceptionAlg, TestManager> FailFilter;
            FilterRTC* f = FilterRTC::create("Fail!", "RaiseExceptionAlg",
                "MangerRTC");
            f->setName(f->getName());
            shouldEqual(strncmp(f->getName().c_str(), "Fail!", 5), 0);
            f->setName("foo");
            shouldEqual(strncmp(f->getName().c_str(), "foo", 3), 0);
            delete f;
        }

};

/** The main function that runs the tests for class BasicFilterRTC.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    FilterRTCTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

