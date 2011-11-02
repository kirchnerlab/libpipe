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


#include <iostream>
#include "vigra/unittest.hxx"
#include "rtc/utils.hpp"
#define private public
#define protected public
#include <libpipe/rtc/Loader.hpp>
#undef private
#undef protected
#include <libpipe/rtc/Pipeline.hpp>


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct LoaderTestSuite : vigra::test_suite
{
        /** Constructor.
         * The rtc/LoaderTestSuite constructor adds all rtc/Loader tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        LoaderTestSuite() :
                vigra::test_suite("rtc/Loader")
        {
            add(testCase(&LoaderTestSuite::testConstruction));
            add(testCase(&LoaderTestSuite::testGetter));

        }

        void testConstruction()
        {
            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"] = "inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
            libpipe::rtc::Loader loader(inputFiles);
            bool thrown=false;
            try{
                std::map<std::string, std::string> inputFiles;
                inputFiles["FilterInput"] = "bla.txt";
                inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
                inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
                libpipe::rtc::Loader loader(inputFiles);
            }catch (...){
                thrown=true;
            }
            shouldEqual(thrown,true);

        }

        void testGetter()
        {
            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"] = "inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
            libpipe::rtc::Loader loader(inputFiles);
            libpipe::rtc::Pipeline pipe = loader.getPipeline();
            //indirect test of equality
            shouldEqual(sizeof(loader.pipeline_), sizeof(pipe));
        }
};

/** The main function that runs the tests for class rtc#Loader.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    LoaderTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

