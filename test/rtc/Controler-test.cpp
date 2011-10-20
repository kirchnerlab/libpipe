/*
 * rtc/Controler-test.cpp
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
            Controler creator("inputFile.txt");
        }

        void testWrongCalls()
        {
            Controler creator("inputFile.txt");

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
            Controler creator("inputFile.txt");
            boost::shared_ptr<Filter> f1 = creator.getFilter("Lowercase");
            shouldEqual(f1->getName(), "Lowercase");
        }

        void testPipeline(){
            Controler creator("inputFile.txt");
            Pipeline pipe=creator.getPipeline();
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

