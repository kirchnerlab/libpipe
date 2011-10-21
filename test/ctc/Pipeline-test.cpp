/*
 * Pipeline-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#define private public
#define protected public
#include <libpipe/ctc/Pipeline.hpp>
#undef private
#undef protected
#include "vigra/unittest.hxx"
#include "ctc/utils.hpp"

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */

using namespace libpipe::ctc;

struct PipelineTestSuite : vigra::test_suite
{
        /** Constructor.
         * The PipelineTestSuite constructor adds all Pipeline tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        PipelineTestSuite() :
                vigra::test_suite("Pipeline")
        {
            add(testCase(&PipelineTestSuite::testPush));
            add(testCase(&PipelineTestSuite::testRunAndTrace));
        }
        void testPush()
        {
            Pipeline pipeline;
            typedef BasicFilter<Identity, TestManager> IdentityFilter;

            boost::shared_ptr<IdentityFilter> f(
                new IdentityFilter(std::string("bla")));

            shouldEqual(pipeline.requestQueue_.empty(), true);
            shouldEqual(pipeline.pipelineQueue_.empty(), true);

            libpipe::Request reqDel(libpipe::Request::DELETE);
            libpipe::Request reqUpd(libpipe::Request::UPDATE);

            pipeline.push(reqDel, boost::dynamic_pointer_cast<Filter>(f));

            shouldEqual(
                f->getName() == pipeline.pipelineQueue_.front()->getName(),
                true);
            shouldEqual(reqDel.type_ == pipeline.requestQueue_.front().type_,
                true);

            shouldEqual(pipeline.requestQueue_.empty(), false);
            shouldEqual(pipeline.pipelineQueue_.empty(), false);

        }

        void testRunAndTrace()
        {
            Pipeline pipeline;
            typedef BasicFilter<Identity, TestManager> IdentityFilter;
            boost::shared_ptr<IdentityFilter> f(
                new IdentityFilter(std::string("bla")));

            libpipe::Request reqUpd(libpipe::Request::UPDATE);

            pipeline.push(reqUpd, boost::dynamic_pointer_cast<Filter>(f));

            bool thrown = false;
            try {
                pipeline.run();
            } catch (libpipe::utilities::Exception& e) {
                thrown = true;
            }

            shouldEqual(thrown, false);

            std::vector<std::string> trace;
            pipeline.getTrace(trace);

            shouldEqual(trace.size(), pipeline.trace_.size());
        }
};

/** The main function that runs the tests for class Pipeline.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    PipelineTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

