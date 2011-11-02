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
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_REQUEST_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_REQUEST_HPP__

#include <libpipe/config.hpp>

#include <vector>
#include <string>
#include <ctime>

#include <libpipe/RequestException.hpp>

#include <boost/thread.hpp>

/** Macro that add an entry to a requests trace.
 * This is just for convenience.
 */
#define LIBPIPE_REQUEST_TRACE(req, str) \
  if (req.getTraceFlag()) \
  req.addTrace(std::string(__FUNCTION__) + ": " + str)

namespace libpipe {

/** A request object.
 * The request object is used to transfer requests between filters. 
 */
class Request
{
    public:
        /** Defines the request type.
         * UPDATE for updating the filters
         * DELETE for deleting the filters
         */
        enum Type
        {
            UPDATE = 0, DELETE = 1
        };

        /** Constructor.
         * Requires a request type.
         * @param[in] t The type of the request.
         */
        Request(const Type& t);

        /**Constructor
         * Type is Update
         */
        Request();

        /** Destructor.
         * Virtual, to allow subclassing.
         */
        virtual ~Request();

        /** Tests the type of a request.
         * @param[in] t A request type.
         * @return true of t is of the same type as this
         */
        bool is(const Type& t);

        /** Returns the type of request
         * @return The Request Type of the request
         */
        Type getType() const;

        /** Returns the state of the trace flag.
         * If the trace flag is on, clients should add trace information
         * while processing the request, using addTrace().
         * @return The state if the trace flag (true == on).
         */
        bool getTraceFlag() const;

        /** Set the state of the trace flag.
         * This allows to switch tracing on and off.
         * @param[in] tf The new trace flag setting (true == on).
         */
        void setTraceFlag(const bool tf);


        /** Returns all traces collected in the Request object.
         * @param[out] trace All collected trace information.
         */
        void getTrace(std::vector<std::string>& trace) const;

        /** Add trace information to the request object.
         * Currently the request object simply collects std::strings.
         * @param[in] t Trace information.
         */
        void addTrace(const std::string& t);

        /** Clears all trace information from the Request object.
         */
        void clearTrace();

        /** Adds the trace to the current request type if the type and flag are the same.
         * @param rhs Request which trace is added to the Request
         * @return the combined request
         */
        Request& operator+=(Request const& rhs);

    protected:

        /** The request type.
         * @see Type
         */
        Type type_;

        /** Trace status.
         * If true, clients receiving the request should store
         * trace information using addTrace().
         * @see addTrace
         */
        bool traceFlag_;

        /** Trace information.
         */
        static std::vector<std::string> trace_;

        static boost::mutex requestMutex_;


};

} // namespace libpipe

#endif

