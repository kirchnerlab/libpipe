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
#include "libpipe/rtc/ConfigJSON.hpp"
#undef private
#undef protected

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */

using namespace libpipe::rtc;

struct ConfigJSONTestSuite : vigra::test_suite
{
        /** Constructor.
         * The rtc/ConfigJSONTestSuite constructor adds all rtc/ConfigJSON tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        ConfigJSONTestSuite() :
                vigra::test_suite("rtc/ConfigJSON")
        {
            add(testCase(&ConfigJSONTestSuite::testInputFileHandling));
            add(testCase(&ConfigJSONTestSuite::testFileChecker));
            add(testCase(&ConfigJSONTestSuite::testGetters));
        }

        void testInputFileHandling()
        {
            bool thrown = false;
            try {
                ConfigJSON test;

                std::map<std::string, std::string> inputFiles;
                inputFiles["sda"] = "inputFileFilterJSON.txt";
                inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
                inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
                test.parseInputFile(inputFiles);
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);

            thrown = false;

            try {
                ConfigJSON test;

                std::map<std::string, std::string> inputFiles;
                inputFiles["FilterInput"]="wrongInputFile.txt";
                inputFiles["ConnectionInput"]="inputFileConnectionJSON.txt";
                inputFiles["PipelineInput"]="inputFilePipelineJSON.txt";
                test.parseInputFile(inputFiles);
            } catch (...) {
                thrown = true;
            }
            shouldEqual(thrown, true);

        }

        void testFileChecker()
        {

            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"]="inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"]="inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"]="inputFilePipelineJSON.txt";
            ConfigJSON test;
            shouldEqual(test.checkFile(inputFiles), true);

        }

        void testGetters()
        {

            std::map<std::string, std::string> inputFiles;
            inputFiles["FilterInput"]="inputFileFilterJSON.txt";
            inputFiles["ConnectionInput"]="inputFileConnectionJSON.txt";
            inputFiles["PipelineInput"]="inputFilePipelineJSON.txt";
            ConfigJSON test;
            test.parseInputFile(inputFiles);

            shouldEqual(int(test.getFilters().size()), 6);

            shouldEqual(int(test.getPort("Combiner").size()), 2);

            shouldEqual(int(test.getPort("Lowercase").size()), 1);

            shouldEqual(int(test.getPrecursorFilter("Combiner").size()), 2);

            shouldEqual(int(test.getLibpipePipe().size()), 3);

            bool thrown = false;
            try {
                test.getPort("blub");
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);

            thrown = false;
            try {
                test.getPrecursorFilter("blub");
            } catch (...) {
                thrown = true;
            }
            shouldEqual(thrown, true);

        }

};

/** The main function that runs the tests for class rtc/ConfigJSON.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ConfigJSONTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

