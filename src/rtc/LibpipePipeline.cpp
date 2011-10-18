/*
 * LibpipePipeline.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#include "libpipe/rtc/LibpipePipeline.hpp"
#include "libpipe/rtc/Manager.hpp"

namespace libpipe {
namespace rtc {

LibpipePipeline::LibpipePipeline()
{
}

LibpipePipeline::~LibpipePipeline()
{
}

void LibpipePipeline::push(Request const & req,
    boost::shared_ptr<Filter> filter)
{
    pipelineQueue_.push(filter);
    requestQueue_.push(req);
}

void LibpipePipeline::getTrace(std::vector<std::string>& trace)
{
    trace = trace_;
}

void LibpipePipeline::run()
{

    while (!pipelineQueue_.empty()) {
        Request tempReq = requestQueue_.front();
        std::string tempStr;
        if (tempReq.getTraceFlag()) {
            if (tempReq.getType() == libpipe::Request::UPDATE) {
                tempStr = "\033[22;31m Starting Update Request\e[m";
            } else if (tempReq.getType() == libpipe::Request::DELETE) {
                tempStr = "\033[22;31m Starting Delete Request\e[m";
            }
        }

        LIBPIPE_REQUEST_TRACE(tempReq, tempStr);

        pipelineQueue_.front()->getManager()->processRequest(tempReq);

        std::vector<std::string> tempTrace;
        tempReq.getTrace(tempTrace);
        trace_.insert(trace_.end(), tempTrace.begin(), tempTrace.end());

        pipelineQueue_.pop();
        requestQueue_.pop();
    }

}

} /* namespace rtc */
} /* namespace libpipe */
