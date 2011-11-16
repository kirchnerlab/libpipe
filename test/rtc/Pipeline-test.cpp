/*
 *
 * Copyright (c) 2011 David-Matthias Sichau
 * Copyright (c) 2010 Marc Kirchner
 *
 * This file is part of libpipe.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <libpipe/config.hpp>

#include <iostream>
#include "vigra/unittest.hxx"
#ifndef  _WIN32
    #define private public
    #define protected public
#endif
#include "libpipe/rtc/PipelineLoader.hpp"
#include "rtc/utils.hpp"
#include "libpipe/rtc/Pipeline.hpp"
#include "libpipe/Request.hpp"
#ifndef  _WIN32
    #undef private
    #undef protected
#endif

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
#ifndef  _WIN32
            add(testCase(&PipelineTestSuite::testPush));
#endif
            add(testCase(&PipelineTestSuite::testRunAndTrace));
            add(testCase(&PipelineTestSuite::testTraceFlag));
            add(testCase(&PipelineTestSuite::testTrace));
        }
#ifndef _WIN32
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
#endif

        void testRunAndTrace()
        {
            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"] = "inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
            PipelineLoader creator(inputFiles);

            Pipeline pipeline = creator.getPipeline();
            bool thrown = false;
            try {
                pipeline.run();
            } catch (libpipe::utilities::Exception& e) {
                thrown = true;
            }shouldEqual(thrown, false);
#ifndef  _WIN32
            std::vector<std::string> trace;
            trace=pipeline.getTrace();

            shouldEqual(trace.size(), pipeline.trace_.size());
#endif
        }
        /** Check trace flag getter/setter
         */
        void testTraceFlag()
        {
            {
                // getset test
                Pipeline pipe;
                pipe.setTraceFlag(pipe.getTraceFlag());
            }
            Pipeline pipe;
            // should be initialized to false
            shouldEqual(pipe.getTraceFlag(), false);
            pipe.setTraceFlag(true);
            shouldEqual(pipe.getTraceFlag(), true);
            pipe.setTraceFlag(false);
            shouldEqual(pipe.getTraceFlag(), false);
        }

        /** Check trace info handling.
         */
        void testTrace()
        {
            Pipeline pipe;
            pipe.clearTrace();
            std::vector<std::string> trace;
            // make sure we initially have an empty trace
            trace=pipe.getTrace();
            shouldEqual(trace.size(), static_cast<size_t>(0));
            trace.clear();
            // add a message and check the size and content again
            std::string message("Some message.");
            pipe.addTrace(message);
            trace=pipe.getTrace();
            shouldEqual(trace.size(), static_cast<size_t>(1));
            // do not compare the date/time part.
            shouldEqual(
                trace[0].substr(trace[0].size()-message.size(), message.size()),
                message);
            trace.clear();
            // clear the trace info from the request object
            pipe.clearTrace();
            trace=pipe.getTrace();
            shouldEqual(trace.size(), static_cast<size_t>(0));
            trace.clear();
            // make sure the traces are sorted
            std::vector<std::string> control;
            for (size_t i = 0; i < 10; ++i) {
                std::ostringstream oss;
                oss << "message no " << i;
                pipe.addTrace(oss.str());
                control.push_back(oss.str());
            }
            trace=pipe.getTrace();
            for (size_t i = 0; i < 10; ++i) {
                shouldEqual(
                    trace[i].substr(trace[i].size()-control[i].size(), control[i].size()),
                    control[i]);
            }
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

