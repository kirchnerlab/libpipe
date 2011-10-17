/*
 * LibpipePipeline.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPEPIPELINE_HPP_
#define LIBPIPEPIPELINE_HPP_

#include "libpipe/Request.hpp"
#include "libpipe/rtc/Filter.hpp"

#include <queue>

#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {



class LibpipePipeline
{
    public:
        LibpipePipeline();
        ~LibpipePipeline();

        void push(Request const & req, boost::shared_ptr<Filter> filter);

        void run();

        void getTrace(std::vector<std::string>& trace);

    private:
        std::queue<boost::shared_ptr<Filter> > pipelineQueue_;

        std::queue<Request> requestQueue_;

       std::vector<std::string> trace_;
};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* LIBPIPEPIPELINE_HPP_ */
