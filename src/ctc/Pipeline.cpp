/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2011 Marc Kirchner
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

#include <libpipe/ctc/Pipeline.hpp>
#include <libpipe/ctc/Manager.hpp>

using namespace libpipe::ctc;

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::push(Request const & req,
    boost::shared_ptr<Filter> filter)
{
    pipelineQueue_.push(filter);
    requestQueue_.push(req);
}

void Pipeline::getTrace(std::vector<std::string>& trace)
{
    trace = trace_;
}

void Pipeline::run()
{

    while (!pipelineQueue_.empty()) {
        Request tempReq = requestQueue_.front();
        std::string tempStr;
        if (Pipeline::getTraceFlag()) {
            if (tempReq.getType() == libpipe::Request::UPDATE) {
                tempStr = "\033[22;31m Starting Update Request\e[m";
            } else if (tempReq.getType() == libpipe::Request::DELETE) {
                tempStr = "\033[22;31m Starting Delete Request\e[m";
            }
        }

        LIBPIPE_PIPELINE_TRACE(tempReq, tempStr);

        pipelineQueue_.front()->getManager()->processRequest(tempReq);

        pipelineQueue_.pop();
        requestQueue_.pop();
    }

}


bool Pipeline::getTraceFlag()
{
    return traceFlag_;
}

void Pipeline::setTraceFlag(const bool tf)
{
    traceFlag_ = tf;
}

std::vector<std::string>& Pipeline::getTrace()
{
    return trace_;
}

void Pipeline::addTrace(const std::string& t)
{
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    static char buffer[40];
    strftime(buffer, 40, "%Y.%m.%d:%H:%M:%S %Z ", timeinfo);
    trace_.push_back(std::string(buffer) + t);
}

void Pipeline::clearTrace()
{
    trace_.clear();
}

std::vector<std::string> Pipeline::trace_;

bool Pipeline::traceFlag_;

