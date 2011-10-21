/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2010 Marc Kirchner
* Copyright (c) 2009 Bernhard Kausler
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

#ifndef __LIBPIPE_INCLUDE_UTILITIES_LIBPIPE_LOG_HPP__
#define __LIBPIPE_INCLUDE_UTILITIES_LIBPIPE_LOG_HPP__

#include <ctime>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>

/**
 * @page log Logging
 *
 * @section usage Usage
 * @c LIBPIPE provides logging to @c stderr via the @c LIBPIPE_LOG macro:
 * @code
 * LIBPIPE_LOG(logINFO) << "Hello" << username 
 *   << "no endl, will be appended automatically";
 * @endcode
 *
 * You can set a plateau logging level:
 * @code
 * #undef LIBPIPE_FILELOG_MAX_LOGGING_LEVEL
 * #define LIBPIPE_FILELOG_MAX_LOGGING_LEVEL libpipe::logWARNING
 * @endcode
 *
 * This can be used to set a global logging level or to construct a fine
 * grained logging structure (for example, different logging levels per file or
 * code segment).
 *
 * The logging macro LIBPIPE_LOG ensures that logging code will only be compiled
 * into the final binary, if it corresponds to the set plateu logging level.
 *
 * <em>
 * The @c Log API should never be used directly. Use the macros provided with @c
 * Log.
 * </em>
 *
 * @section logginglevels Logging levels
 * The following logging levels are available (ordered by decreasing urgency):
 * @code
 * logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4
 * @endcode
 *
 * @section disablelogging Turning off logging
 * In order to turn all logging facilities off, a special logging level is
 * provided:
 * @code
 * logNO_LOGGING
 * @endcode
 * Set as the plateau logging level, no logging code will be compiled in the
 * final binary. Obviously, this is provided mostly for completeness; any
 * software based on LIBPIPE should provide at least error logging.
 * <em>
 * The special logNO_LOGGING level is NOT a valid paramter to LIBPIPE_LOG.
 * </em>
 */

namespace libpipe {

namespace utilities {

/** Returns a std::string representation of the current time, in millisecond
 * resolution.
 * Returns a strng representation of the current system time:
 * @code
 * 15:50:57.979
 * @endcode
 * The exact presentation of the string is locale dependent.
 */
inline std::string nowTime();

/** Defines all available logging levels.
 * Assign one of these logging levels to each message.
 * @note Do not use @c logNO_LOGGING as a argument to @c LIBPIPE_LOG (only used to
 * turn off logging; defaults to @c logINFO if used).
 */
enum LogLevel
{
    logNO_LOGGING,
    logERROR,
    logWARNING,
    logINFO,
    logDEBUG,
    logDEBUG1,
    logDEBUG2,
    logDEBUG3,
    logDEBUG4
};

/** Redirect the logging stream to a file handle.
 * At the moment, the file handle is hardcoded to 'stderr'.
 * Used in conjunction with the @c Log<T> class: @c Log<Output2FILE>.
 */
class Output2FILE
{
public:
    /** Returns the file handle of the logging stream traget..
     */
    static FILE*& getRedirect();

    /** Writes message to file handle.
     * This function is used in @c Log<T> and must be provided by 
     * every redirector implementation.
     *
     * @param[in] msg Message that is written to the file handle.
     */
    static void output(const std::string& msg);
};

inline FILE*& Output2FILE::getRedirect()
{
    // hardcode stderr
    static FILE* pStream = stderr;
    return pStream;
}

inline void Output2FILE::output(const std::string& msg)
{
    FILE* pStream = getRedirect();
    if (!pStream) {
        return;
    }
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}

/** A thread-safe logging implementation.
 * Log<T> passes its internal logging stream to a redirector T. The redirector
 * is responsible for routing the log information to e.g. a file, syslog, etc.
 * 
 * Any class @c T that provides a method
 * @code
 * void T::output(const std::string& msg)
 * @endcode
 * is considered a redirector.
 */
template<typename T>
class Log
{
public:
    /** Constructor.
     */
    Log();

    /** Destructor.
     * Virtual, to allow subclassing.
     */
    virtual ~Log();

    /** Returns a reference to the logging stream.
     * Calling this function writes something like the following into the internal logging
     * stream (depending on the chosen logging level and the current time):
     * @code
     * '- 16:17:23.714 WARNING: '
     * @endcode
     * Afterwards, it returns a reference to that internal stream and the user
     * can append the respective logging message.
     * @param[in] level The logging level.
     * @return A reference to the logging stream.
     */
    std::ostringstream& get(LogLevel level = logINFO);

    /** Returns the least important logging level available.
     *
     * This function can be used as a safeguard in the logging macros to defend against illegal
     * user defined global logging levels.
     *
     * @return The deepest libpipe::LogLevel available.
     */
    static LogLevel& getReportingLevel();

    /** Converts enumerated logging level to a string.
     *
     * @param level A predefined logging level (e.g. @c logINFO).
     * @return A string representation of the logging level (e.g. "@c INFO").
     */
    static std::string toString(LogLevel level);

    /** Converts a logging level string representation back to the respective
     * enumerated logging level.
     *
     * @param level A string representation of the logging level 
     *              (e.g. "@c INFO")
     * @return The logging level corresponding to the string representation
     *         (e.g. @c logINFO).
     */
    static LogLevel fromString(const std::string& level);

protected:
    /** String stream that holds the logging message(s).
     * Upon destruction of the @c Log<T> object, this stream is written to the
     * redirector T.
     */
    std::ostringstream os_;

private:

    /** Copy constructor.
     * Declared as private and never defined to disallow copying.
     *  
     * @param[in] rhs A right hand side @c Log object.
     */
    Log(const Log& rhs);

    /** Assignment operator.
     * Declared as private and never defined to disallow assignment.
     *  
     * @param[in] rhs A right hand side @c Log object.
     */
    Log& operator=(const Log& rhs);
};

//
// Template implementation
//

template<typename T>
Log<T>::Log()
{
}

template<typename T>
std::ostringstream& Log<T>::get(LogLevel level)
{
    // check if logging level is valid 
    LogLevel ll = level;
    if (ll <= logNO_LOGGING || ll > getReportingLevel()) {
        Log<T> ().get(logWARNING) << "Log<T>::get(): Invalid logging level '"
                << ll << "'. Using INFO level as default.";
        ll = logINFO;
    }

    // print logging preamble to logging stream
    os_ << "- " << nowTime();
    os_ << " " << toString(ll) << ": ";
    os_ << std::string(ll > logDEBUG ? ll - logDEBUG : 0, '\t');

    return os_;
}

template<typename T>
Log<T>::~Log()
{
    // terminate the log stream and make sure it flushes.
    os_ << std::endl;
    // pass the string to the redirector.
    T::output(os_.str());
}

template<typename T>
LogLevel& Log<T>::getReportingLevel()
{
    static LogLevel reportingLevel = logDEBUG4;
    return reportingLevel;
}

template<typename T>
std::string Log<T>::toString(LogLevel level)
{
    if (level > getReportingLevel() || level < logNO_LOGGING) {
        Log<T> ().get(logWARNING)
                << "Log<T>::toString(): Unknown logging level '" << level
                << "'. Using INFO level as default.";
        level = logINFO;
    }
    static const char* const buffer[] = { "NO_LOGGING", "ERROR", "WARNING",
                                          "INFO", "DEBUG", "DEBUG1", "DEBUG2",
                                          "DEBUG3", "DEBUG4" };
    return buffer[level];
}

template<typename T>
LogLevel Log<T>::fromString(const std::string& level)
{
    // tedious...
    if (level == "DEBUG4")
        return logDEBUG4;
    if (level == "DEBUG3")
        return logDEBUG3;
    if (level == "DEBUG2")
        return logDEBUG2;
    if (level == "DEBUG1")
        return logDEBUG1;
    if (level == "DEBUG")
        return logDEBUG;
    if (level == "INFO")
        return logINFO;
    if (level == "WARNING")
        return logWARNING;
    if (level == "ERROR")
        return logERROR;
    if (level == "NO_LOGGING")
        return logNO_LOGGING;
    // default to logINFO
    Log<T> ().get(logWARNING)
            << "Log<T>::fromString(): Unknown logging level '" << level
            << "'. Using INFO level as default.";
    return logINFO;
}

/** A file logger.
 * A class derived from @c Log<T> that writes to stderr.
 */
class FILELog : public Log<Output2FILE>
{
};

#ifndef LIBPIPE_FILELOG_MAX_LOGGING_LEVEL
/** The deepest logging level to be compiled into the code.
 * Any logging message at a deeper level of detail will not be compiled into
 * the code.
 */

#define LIBPIPE_FILELOG_MAX_LOGGING_LEVEL libpipe::utilities::logDEBUG4
#endif

/** Default LIBPIPE logging macro.
 * The macro checks if the logging level should be compiled, creates an
 * anonymous instance of FILELog and writes to its logging stream. Upon
 * desctruction of the anonymous object, the logging message is flushed to
 * stderr.
 *
 * Usage:
 * @code
 * LIBPIPE_LOG(logINFO) << "some logging" << 1224 
 *   << "no endl, will be appended automatically";
 * @endcode
 */
#define LIBPIPE_LOG(level) \
    if (level > LIBPIPE_FILELOG_MAX_LOGGING_LEVEL) ;\
    else if (level > libpipe::utilities::FILELog::getReportingLevel() || !libpipe::utilities::Output2FILE::getRedirect()) ; \
    else libpipe::utilities::FILELog().get(level)

// We have to do the following yaketiyak, because the standard <ctime> is not thread safe.
// (It is using static internal buffers in some functions like ctime() .)
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
} // Temporarily close the LIBPIPE namespace to include the external Windows headers.
// winsocks2.h has always to be included BEFORE windows.h
// We don't use winsocks2 here, but it may be used in a file including this header.
#include <winsock2.h>
#include <windows.h>

// Reopen the LIBPIPE namespace.
namespace libpipe {

inline std::string nowTime()
{
    const int MAX_LEN = 200;
    char buffer[MAX_LEN];

    // get time
    if (GetTimeFormatA(
                    LOCALE_USER_DEFAULT, // locale
                    0, // time format flags
                    0, // optional ptr to systemtime structure
                    "HH':'mm':'ss", // format
                    buffer, // ptr to output buffer
                    MAX_LEN) // size of output buffer
            == 0) {
        return "Error in nowTime()";
    }

    // format time according to our format: "hh:mm:ss.ms"
    static DWORD first = GetTickCount();
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000);

    return result;
}
#else /* not on a windows system */
} // Temporarily close ms namespace to inclue header files.
}
#include <sys/time.h>

// reopen the LIBPIPE namespace
namespace libpipe {
namespace utilities {

inline std::string nowTime()
{
    // get time
    time_t t;
    t = time(NULL);
    if (t == static_cast<std::time_t> (-1)) {
        return "Error_in_nowTime().time";
    }

    // convert time to local time
    tm r = { 0 };
    if (localtime_r(&t, &r) == NULL) {
        return "Error_in_nowTime().localtime_r";
    }

    // convert localtime to a string
    char buffer[101];
    if (strftime(buffer, sizeof(buffer), "%X", &r) == 0) {
        return "Error_in_nowTime().strftime";
    }

    // format the string according to our format: "hh:mm:ss.ms"
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[101] = { 0 };
    std::sprintf(result, "%s.%03ld", buffer, (long) tv.tv_usec / 1000);

    return result;
}
#endif //WIN32
} // end namespace utilities
} // end namespace libpipe

#endif //__LIBPIPE_INCLUDE_UTILITIES_LIBPIPE_LOG_HPP__

