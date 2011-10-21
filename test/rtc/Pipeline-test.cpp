/*
 * rtc/Pipeline-test.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 *
 */
#include <libpipe/config.hpp>

#include <iostream>
#include "vigra/unittest.hxx"
#define private public
#define protected public
#include "libpipe/rtc/Controler.hpp"
#include "rtc/utils.hpp"
#include "libpipe/rtc/Pipeline.hpp"
#include "libpipe/Request.hpp"
#undef private
#undef protected

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
using namespace libpipe::rtc;
struct PipelineTestSuite : vigra::test_suite
{
        /** Constructor.
         * The rtc#LibpipePipelineTestSuite constructor adds all rtc#LibpipePipeline tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        PipelineTestSuite() :
                vigra::test_suite("rtc/Pipeline")
        {
            add(testCase(&PipelineTestSuite::testPush));
            add(testCase(&PipelineTestSuite::testRunAndTrace));
        }

        void testPush()
        {

            Pipeline pipeline;

            boost::shared_ptr<Filter> f(
                libpipe::rtc::Filter::create("filter1", "IdentityRTC",
                    "MangerRTC"));

            shouldEqual(pipeline.requestQueue_.empty(), true);
            shouldEqual(pipeline.pipelineQueue_.empty(), true);

            libpipe::Request reqDel(libpipe::Request::DELETE);
            libpipe::Request reqUpd(libpipe::Request::UPDATE);

            pipeline.push(reqDel, f);

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
            Controler creator("inputFile.txt");

            Pipeline pipeline = creator.getPipeline();
            bool thrown = false;
            try {
                pipeline.run();
            } catch (libpipe::utilities::Exception& e) {
                thrown = true;
            }shouldEqual(thrown, false);

            std::vector<std::string> trace;
            pipeline.getTrace(trace);

            shouldEqual(trace.size(), pipeline.trace_.size());
        }
};

/** The main function that runs the tests for class rtc#LibpipePipeline.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    PipelineTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

