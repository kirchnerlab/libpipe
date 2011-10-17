/*
 * LibpipePipeline.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#include "LibpipePipeline.hpp"

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

        LIBPIPE_REQUEST_TRACE(tempReq, "Starting.");
        try {
            pipelineQueue_.front()->getManager()->processRequest(tempReq);

        } catch (libpipe::RequestException& e) {
            std::cerr << e.what() << std::endl;
        }
        std::vector<std::string> tempTrace;
        tempReq.getTrace(tempTrace);
        trace_.insert(trace_.end(), tempTrace.begin(), tempTrace.end() );

        pipelineQueue_.pop();
        requestQueue_.pop();
    }

}

} /* namespace rtc */
} /* namespace libpipe */
