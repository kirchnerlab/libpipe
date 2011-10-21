/*
 * LibpipePipeline.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
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

