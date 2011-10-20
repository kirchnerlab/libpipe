/*
 * rtc#LibpipeConfigLibconfig-test.cpp
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
#include "libpipe/rtc/ConfigLibconfig.hpp"
#undef private
#undef protected

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */

using namespace libpipe::rtc;

struct ConfigLibconfigTestSuite : vigra::test_suite
{
        /** Constructor.
         * The rtc#LibpipeConfigLibconfigTestSuite constructor adds all rtc#LibpipeConfigLibconfig tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        ConfigLibconfigTestSuite() :
                vigra::test_suite("rtc/ConfigLibconfig")
        {
            add(
                testCase(&ConfigLibconfigTestSuite::testInputFileHandling));
            add(testCase(&ConfigLibconfigTestSuite::testGetters));
        }

        void testInputFileHandling()
        {
            bool thrown = false;
            try {
                ConfigLibconfig test;
                test.parseInputFile("blub.txt");
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);

            thrown = false;

            try {
                ConfigLibconfig test;
                test.parseInputFile("inputFile.txt");
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, false);

            try {
                ConfigLibconfig test;
                test.parseInputFile("wrongInputFile.txt");
            } catch (...) {
                thrown = true;
            }
            shouldEqual(thrown, true);
        }

        void testGetters()
        {

            ConfigLibconfig test;
            test.parseInputFile("inputFile.txt");

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

/** The main function that runs the tests for class rtc#LibpipeConfigLibconfig.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ConfigLibconfigTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

