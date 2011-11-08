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
#define private public
#define protected public
#include "libpipe/rtc/PipelineLoader.hpp"
#include "libpipe/rtc/Pipeline.hpp"
#undef private
#undef protected

#include "rtc/utils.hpp"

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */

using namespace libpipe::rtc;
struct ControlerTestSuite : vigra::test_suite
{
        /** Constructor.
         * The rtc#LibpipeCreatorTestSuite constructor adds all rtc#LibpipeCreator tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        ControlerTestSuite() :
                vigra::test_suite("rtc/Controler")
        {
            add(testCase(&ControlerTestSuite::testMemory));
            add(testCase(&ControlerTestSuite::testWrongCalls));
            add(testCase(&ControlerTestSuite::testFilter));
            add(testCase(&ControlerTestSuite::testPipeline));

        }

        void testMemory()
        {
            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"] = "inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
            PipelineLoader creator(inputFiles);
        }

        void testWrongCalls()
        {
            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"] = "inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
            PipelineLoader creator(inputFiles);
            bool thrown = false;
            try {
                creator.connectManagers("blubblub");
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);

            thrown = false;
            try {
                creator.connectAlgorithmPorts("blubblub");
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);

            thrown = false;
            try {
                creator.getFilter("blubblub");
            } catch (...) {
                thrown = true;
            }
            shouldEqual(thrown, true);
        }

        void testFilter()
        {
            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"] = "inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
            PipelineLoader creator(inputFiles);
            boost::shared_ptr<Filter> f1 = creator.getFilter("Lowercase");
            shouldEqual(f1->getName(), "Lowercase");
        }

        void testPipeline()
        {
            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"] = "inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
            PipelineLoader creator(inputFiles);
            Pipeline pipe = creator.getPipeline();
            shouldEqual(pipe.pipelineQueue_.front()->getName(), "Lowercase");
        }
};

/** The main function that runs the tests for class rtc#LibpipeCreator.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ControlerTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

