/*
 * ManagerRTC-test.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 *
 */
#define private public
#define protected public
#include <libpipe/rtc/Manager.hpp>
#undef private
#undef protected
#include <iostream>
#include "vigra/unittest.hxx"
#include <exception>
#include <stdexcept>
#include <vector>
#include <string>

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Filter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>



#include <libpipe/rtc/LibpipeFactories.hpp>

#include <boost/pointer_cast.hpp>

#include "rtc/utils.hpp"


using namespace libpipe::rtc;
/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct ManagerRTCTestSuite : vigra::test_suite
{
        /** Constructor.
         * The ManagerRTCTestSuite constructor adds all ManagerRTC tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        ManagerRTCTestSuite() :
                vigra::test_suite("ManagerRTC")
        {
            add(testCase(&ManagerRTCTestSuite::testSetAlgorithm));
            add(testCase(&ManagerRTCTestSuite::testSharedPtr));
            add(testCase(&ManagerRTCTestSuite::testConnect));
            add(
                testCase(&ManagerRTCTestSuite::testProcessRequestNoAlgorithmSetup));
            add(testCase(&ManagerRTCTestSuite::testProcessRequestNoSources));
            add(
                testCase(&ManagerRTCTestSuite::testProcessRequestFailingSources));
            add(
                testCase(&ManagerRTCTestSuite::testProcessRequestFailingSourcesDelete));
        }

        /** Setting the algorithm.
         */
        void testSetAlgorithm()
        {
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "IdentityRTC");
            Manager* m = ManagerFactory::instance().createObject("MangerRTC");
            m->setAlgorithm(a);
            std::cout<<m->getAlgorithm()<<"b"<<a<<std::endl;
            // make sure the pointers point at the same location
            shouldEqual(m->getAlgorithm(), a);
            delete a;
            delete m;

        }

        /** Test shared_ptr
         */
        void testSharedPtr()
        {
            boost::shared_ptr<Filter> fi(
                Filter::create("Filter 1: ID", "IdentityRTC", "MangerRTC"));
            shouldEqual(fi.use_count(), 1);
            shouldEqual(fi.unique(), true);

            boost::shared_ptr<Filter> ff(fi);

            shouldEqual(fi.use_count(), 2);
            shouldEqual(fi.unique(), false);
            shouldEqual(ff, fi);

            fi.reset();
            shouldEqual(fi.use_count(), 0);
            shouldEqual(ff.use_count(), 1);
            shouldEqual(ff.unique(), true);

        }

        /** Test source setup, i.e. connecting.
         */
        void testConnect()
        {
            // Use a derived class to gain access to the source list.
            Manager* tm = ManagerFactory::instance().createObject(
                "MangerRTC");
            shouldEqual(tm->getSources().size(), static_cast<size_t>(0));

            boost::shared_ptr<Filter> fi(
                Filter::create("Filter 1: ID", "IdentityRTC", "MangerRTC"));

            tm->connect(fi);
            shouldEqual(tm->getSources().size(), static_cast<size_t>(1));

            boost::shared_ptr<Filter> ff(
                Filter::create("Filter 2: FAILER", "RaiseExceptionAlg",
                    "MangerRTC"));

            tm->connect(ff);
            shouldEqual(tm->getSources().size(), static_cast<size_t>(2));
            delete tm;

        }

        /** Request processing w/o a defined algorithm.
         */
        void testProcessRequestNoAlgorithmSetup()
        {
            // make sure we fail if there is no algorithm setup
            Manager* tm = ManagerFactory::instance().createObject(
                "MangerRTC");
            libpipe::Request req(libpipe::Request::UPDATE);
            bool thrown = false;
            // FIXME: we should have different error classes to distinguish
            //        between different errors.
            try {
                req = tm->processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);
            delete tm;

        }

        /** Request processing with no sources and a successful algorithm.
         */
        void testProcessRequestNoSources()
        {
            Manager* tm = ManagerFactory::instance().createObject(
                "MangerRTC");
            libpipe::Request req(libpipe::Request::UPDATE);
            req.setTraceFlag(true);
            // the following algorithm should not throw any exceptions
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "IdentityRTC");
            tm->setAlgorithm(a);
            shouldEqual(tm->getSources().size(), static_cast<size_t>(0));
            req = tm->processRequest(req);
            delete a;
            std::vector<std::string> trace;
            req.getTrace(trace);
            shouldEqual(trace.size(), static_cast<size_t>(1));
            // now let the algorithm throw an exception
            Algorithm* b = AlgorithmFactory::instance().createObject(
                "RaiseExceptionAlg");
            tm->setAlgorithm(b);
            bool thrown = false;
            try {
                req = tm->processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);
            delete b;
            delete tm;

        }

        /** Request processing if one of the sources fails.
         */
        void testProcessRequestFailingSources()
        {
            Manager* tm = ManagerFactory::instance().createObject(
                "MangerRTC");
            libpipe::Request req(libpipe::Request::UPDATE);

            Algorithm* a = AlgorithmFactory::instance().createObject(
                "IdentityRTC");
            tm->setAlgorithm(a);

            boost::shared_ptr<Filter> fi(
                Filter::create("Id", "IdentityRTC", "MangerRTC"));
            fi->getManager()->setAlgorithm(a);

            tm->connect(boost::dynamic_pointer_cast<Filter>(fi));

            // this is the ok source

            req = tm->processRequest(req);

            // now add the failing source

            boost::shared_ptr<Filter> ff(Filter::create("FailFilter","RaiseExceptionAlg", "MangerRTC"));

            tm->connect(ff);

            bool thrown = false;
            try {
                req = tm->processRequest(req);
            } catch (libpipe::RequestException& e) {
                thrown = true;
            }shouldEqual(thrown, true);

            delete a;
            delete tm;

        }
        /** Request processing if the request type is delete.
         */
        void testProcessRequestFailingSourcesDelete()
        {
            Manager* tm = ManagerFactory::instance().createObject(
                "MangerRTC");
            libpipe::Request req(libpipe::Request::DELETE);
            Algorithm* a = AlgorithmFactory::instance().createObject(
                "IdentityRTC");
            tm->setAlgorithm(a);

            boost::shared_ptr<Filter> fi(
                Filter::create("Id", "IdentityRTC", "MangerRTC"));

            tm->connect(boost::dynamic_pointer_cast<Filter>(fi));

            // make sure that the filters are deleted
            shouldEqual(tm->getSources().size(), static_cast<size_t>(1));
            req = tm->processRequest(req);
            shouldEqual(tm->getSources().size(), static_cast<size_t>(0));
            shouldEqual(tm->getAlgorithm()->needUpdate(), false);

            delete a;
            delete tm;
        }
};

/** The main function that runs the tests for class ManagerRTC.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ManagerRTCTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

