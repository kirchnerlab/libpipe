/*
 * FilterRTC-test.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 *
 */

#include <iostream>
#include <cstring>

#include "vigra/unittest.hxx"
#define private public
#define protected public
#include <libpipe/rtc/Filter.hpp>
#undef private
#undef protected
#include <libpipe/rtc/LibpipeFactories.hpp>

#include <typeinfo>

#include "rtc/utils.hpp"

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */

using namespace libpipe::rtc;
struct FilterRTCTestSuite : vigra::test_suite
{
        /** Constructor.
         * The BasicFilterRTCTestSuite constructor adds all BasicFilterRTC tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        FilterRTCTestSuite() :
                vigra::test_suite("rtc/Filter")
        {
            add(testCase(&FilterRTCTestSuite::testConstructionAndDestruction));
            add(testCase(&FilterRTCTestSuite::testAlgorithm));
            add(testCase(&FilterRTCTestSuite::testManager));
            add(testCase(&FilterRTCTestSuite::testCallChain));
            add(testCase(&FilterRTCTestSuite::testName));
        }

        void testConstructionAndDestruction()
        {

            libpipe::rtc::Filter* bf = libpipe::rtc::Filter::create(
                "filter1", "IdentityRTC", "MangerRTC");
            libpipe::rtc::Algorithm* iA =
                    libpipe::rtc::AlgorithmFactory::instance().createObject(
                        "IdentityRTC");
            shouldEqual(typeid(iA)==typeid(bf->getAlgorithm()), true);
            delete bf;
            delete iA;
        }

        void testAlgorithm()
        {
            // getset
            libpipe::rtc::Filter* bf = libpipe::rtc::Filter::create(
                "filter1", "RaiseExceptionAlg", "MangerRTC");
            libpipe::rtc::Algorithm* p = bf->getAlgorithm();
            shouldEqual(bf->getAlgorithm(), p);
            // switch algorithm

            Algorithm* c = AlgorithmFactory::instance().createObject("IdentityRTC");

            bf->setAlgorithm(c);

            shouldEqual(bf->getAlgorithm(),c);

            delete bf;

        }

        void testManager()
        {
            // getset
            libpipe::rtc::Filter* bf = libpipe::rtc::Filter::create(
                            "filter1", "RaiseExceptionAlg", "MangerRTC");
            libpipe::rtc::Manager* p = bf->getManager();
            shouldEqual(bf->getManager(), p);

            Manager* m = ManagerFactory::instance().createObject("MangerRTC");
            bf->setManager(m);
            shouldEqual(bf->getManager(),m);

            delete bf;
        }

        void testCallChain()
        {
            using namespace libpipe::rtc;
            // tests if the filter calls its managers process request function
            // the manager will then call the process request function of the fail
            // filter and raise an exception.
            Filter* f = Filter::create("fail Filter",
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
            Filter* f = Filter::create("Fail!", "RaiseExceptionAlg",
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

