/*
 * Loader-test.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 *
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
            std::vector<std::string> inputFiles;
            inputFiles.push_back("inputFileFilterJSON.txt");
            inputFiles.push_back("inputFileConnectionJSON.txt");
            inputFiles.push_back("inputFilePipelineJSON.txt");
            libpipe::rtc::Loader loader(inputFiles);
            bool thrown=false;
            try{
                std::vector<std::string> inputFiles;
                inputFiles.push_back("bla.txt");
                libpipe::rtc::Loader loader(inputFiles);
            }catch (...){
                thrown=true;
            }
            shouldEqual(thrown,false);

        }

        void testGetter()
        {
            std::vector<std::string> inputFiles;
            inputFiles.push_back("inputFileFilterJSON.txt");
            inputFiles.push_back("inputFileConnectionJSON.txt");
            inputFiles.push_back("inputFilePipelineJSON.txt");
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

