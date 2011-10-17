/*
 * rtc#LibpipeCreator-test.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#define private public
#define protected public
#include "libpipe/rtc/LibpipeCreator.hpp"
#include "libpipe/rtc/LibpipePipeline.hpp"
#undef private
#undef protected


#include "rtc/utils.hpp"

#include "libpipe/rtc/LibpipeFactories.hpp"

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */

using namespace libpipe::rtc;
struct LibpipeCreatorTestSuite : vigra::test_suite
{
        /** Constructor.
         * The rtc#LibpipeCreatorTestSuite constructor adds all rtc#LibpipeCreator tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        LibpipeCreatorTestSuite() :
                vigra::test_suite("rtc/LibpipeCreator")
        {
            add(testCase(&LibpipeCreatorTestSuite::testMemory));
            add(testCase(&LibpipeCreatorTestSuite::testWrongCalls));
            add(testCase(&LibpipeCreatorTestSuite::testFilter));
            add(testCase(&LibpipeCreatorTestSuite::testPipeline));


        }

        void testMemory()
        {
            LibpipeCreator creator("inputFile.txt");
        }

        void testWrongCalls()
        {
            LibpipeCreator creator("inputFile.txt");

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

        void testFilter(){
            LibpipeCreator creator("inputFile.txt");
            boost::shared_ptr<Filter> f1 = creator.getFilter("LowercaseFilter");
            shouldEqual(f1->getName(), "LowercaseFilter");
        }

        void testPipeline(){
            LibpipeCreator creator("inputFile.txt");
            LibpipePipeline pipe=creator.getPipeline();
            shouldEqual(pipe.pipelineQueue_.front()->getName(), "LowercaseFilter");
        }
};

/** The main function that runs the tests for class rtc#LibpipeCreator.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    LibpipeCreatorTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

