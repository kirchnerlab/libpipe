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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_PIPELINE_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_PIPELINE_HPP__

#include <libpipe/config.hpp>

#include <libpipe/Request.hpp>
#include <libpipe/rtc/Filter.hpp>

#include <queue>

#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {

class Pipeline
{
    public:
        Pipeline();
        ~Pipeline();

        /** Add a filter and request on top of the queue.
         * @param req The Request which will be processed by the filter
         * @param filter The filter which handles the request.
         */
        void push(Request const & req, boost::shared_ptr<Filter> filter);

        /** Will run all requests in the queue. This needs to be called to run Libpipe.
         */
        void run();

        /** Returns the trace.
         * @param trace [out] The trace of this libpipe pipeline.
         */
        void getTrace(std::vector<std::string>& trace);

    private:
        std::queue<boost::shared_ptr<Filter> > pipelineQueue_;

        std::queue<Request> requestQueue_;

        std::vector<std::string> trace_;
};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_PIPELINE_HPP__ */
