/* 
 * Log-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 * Copyright (c) 2009 Bernhard Kausler
 *
 */

#include <cstring>
#include <iostream>
#include <ostream>
#include <cstdio>

#include <libpipe/utilities/Log.hpp>
#include "vigra/unittest.hxx"

using namespace libpipe::utilities;

struct LogTestSuite : vigra::test_suite
{
    LogTestSuite() :
        vigra::test_suite("Logging")
    {
        add(testCase(&LogTestSuite::testFILELog));
        add(testCase(&LogTestSuite::testOutput2FILE));
        add(testCase(&LogTestSuite::testMacros));
        add(testCase(&LogTestSuite::testNowTime));
    }

    void testOutput2FILE()
    {
        Output2FILE out;
        // getStream()
        should(out.getRedirect() == stderr);
        // output()
        out.output("Some logging message");
    }

    // implicitly, this tests the Log<T> too
    void testFILELog()
    {
        FILELog l;

        shouldEqual(l.fromString("DEBUG4"), logDEBUG4);
        shouldEqual(l.fromString("DEBUG3"), logDEBUG3);
        shouldEqual(l.fromString("DEBUG2"), logDEBUG2);
        shouldEqual(l.fromString("DEBUG1"), logDEBUG1);
        shouldEqual(l.fromString("DEBUG"), logDEBUG);
        shouldEqual(l.fromString("INFO"), logINFO);
        shouldEqual(l.fromString("WARNING"), logWARNING);
        shouldEqual(l.fromString("ERROR"), logERROR);
        shouldEqual(l.fromString("NO_LOGGING"), logNO_LOGGING);
        shouldEqual(l.fromString("something else"), logINFO);

        should(l.toString(logDEBUG4) == "DEBUG4");
        should(l.toString(logDEBUG3) == "DEBUG3");
        should(l.toString(logDEBUG2) == "DEBUG2");
        should(l.toString(logDEBUG1) == "DEBUG1");
        should(l.toString(logDEBUG) == "DEBUG");
        should(l.toString(logINFO) == "INFO");
        should(l.toString(logWARNING) == "WARNING");
        should(l.toString(logERROR) == "ERROR");
        should(l.toString(logNO_LOGGING) == "NO_LOGGING");
        // invalid input
        should(l.toString((LogLevel)(-1)) == "INFO");
        // getReportingLevel()
        shouldEqual(l.getReportingLevel(), logDEBUG4);
        // get()
        l.get();
        l.get(logDEBUG4);
        l.get(logDEBUG3);
        l.get(logDEBUG2);
        l.get(logDEBUG1);
        l.get(logDEBUG);
        l.get(logINFO);
        l.get(logWARNING);
        l.get(logERROR);
        l.get(logNO_LOGGING); // should default to INFO
        l.get((LogLevel) (-1)); // invalid input
        // test intended usage
        FILELog().get() << "Test of intended usage";
    }

    void testMacros()
    {
        // LIBPIPE_LOG
        LIBPIPE_LOG(logINFO)
                << "Macro test.";

        // max level mechanism
#undef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logINFO
        LIBPIPE_LOG(logWARNING)
                << "This should be logged, since WARNING is above INFO.";
        LIBPIPE_LOG(logDEBUG)
                << "This SHOULDN'T be logged, since DEBUG is below INFO!";

        // reset to standard max level
#undef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logDEBUG4
        LIBPIPE_LOG(logDEBUG1)
                << "This should be logged again, since we reset to logDEBUG4.";
    }

    void testNowTime()
    {
        nowTime();
    }
};

int main()
{
    LogTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

