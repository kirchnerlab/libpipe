/*
 * rtc#LibpipePipeline-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#define private public
#define protected public
#include "rtc/utils.hpp"
#include "libpipe/rtc/LibpipePipeline.hpp"
#include "libpipe/Request.hpp"
#undef private
#undef protected

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
using namespace libpipe::rtc;
struct LibpipePipelineTestSuite : vigra::test_suite
{
        /** Constructor.
         * The rtc#LibpipePipelineTestSuite constructor adds all rtc#LibpipePipeline tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        LibpipePipelineTestSuite() :
                vigra::test_suite("rtc/LibpipePipeline")
        {
            add(testCase(&LibpipePipelineTestSuite::testPush));
            add(testCase(&LibpipePipelineTestSuite::testRunAndTrace));
        }

        void testPush()
        {

            LibpipePipeline pipeline;

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
            LibpipeCreator creator("inputFile.txt");

            LibpipePipeline pipeline = creator.getPipeline();
            bool thrown = false;
            try {
                pipeline.run();
            } catch (libpipe::Exception& e) {
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
    LibpipePipelineTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

