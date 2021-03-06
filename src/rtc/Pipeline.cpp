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

#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/rtc/Manager.hpp>
#include <ctime>

namespace libpipe {
namespace rtc {

Pipeline::Pipeline()
{
    setTraceFlag(false);
}

Pipeline::~Pipeline()
{
}

void Pipeline::push(Request const & req, boost::shared_ptr<Filter> filter)
{
    pipelineQueue_.push(filter);
    requestQueue_.push(req);
}

void Pipeline::run()
{
    while (!pipelineQueue_.empty()) {
        Request tempReq = requestQueue_.front();
        std::string tempStr;
        if (Pipeline::getTraceFlag()) {
            if (tempReq.getType() == libpipe::Request::UPDATE) {
                tempStr = "Starting Update Request";
            } else if (tempReq.getType() == libpipe::Request::DELETE) {
                tempStr = "Starting Delete Request";
            }
        }

        LIBPIPE_PIPELINE_TRACE(tempStr);
#ifdef ENABLE_THREADING
        boost::exception_ptr error;
        pipelineQueue_.front()->processThreadedRequest(tempReq, error);
        if (error) {
            boost::rethrow_exception(error);
        }
#else

        pipelineQueue_.front()->processRequest(tempReq);
#endif

        pipelineQueue_.pop();
        requestQueue_.pop();
    }
}

bool Pipeline::getTraceFlag()
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(traceFlagMutex_);
#endif
    return traceFlag_;
}

void Pipeline::setTraceFlag(const bool tf)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(traceFlagMutex_);
#endif
    traceFlag_ = tf;
}

std::vector<std::string>& Pipeline::getTrace()
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(traceMutex_);
#endif
    return trace_;
}

void Pipeline::addTrace(const std::string& t)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(traceMutex_);
#endif
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    static char buffer[40];
    strftime(buffer, 40, "%Y.%m.%d:%H:%M:%S %Z ", timeinfo);
#ifdef ENABLE_THREADING
    std::ostringstream thread;
    thread << "thread: " << boost::this_thread::get_id() << "\t";
    trace_.push_back(thread.str() + std::string(buffer) + t);
#else
    trace_.push_back(std::string(buffer) + t);
#endif

}

void Pipeline::clearTrace()
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(traceMutex_);
#endif
    trace_.clear();
}

std::vector<std::string> Pipeline::trace_;

bool Pipeline::traceFlag_;
#ifdef ENABLE_THREADING
boost::shared_mutex Pipeline::traceMutex_;
boost::shared_mutex Pipeline::traceFlagMutex_;
#endif



} /* namespace rtc */
} /* namespace libpipe */
