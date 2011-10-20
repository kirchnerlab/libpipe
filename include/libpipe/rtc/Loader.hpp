/*
 * Loader.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__

#include <libpipe/config.hpp>

#include <libpipe/rtc/Pipeline.hpp>
#include <string>

namespace libpipe {
namespace rtc {


class Loader
{
    public:
        Loader(const std::string& filename);
        ~Loader();

        Pipeline getPipeline() const;

    private:
        Pipeline pipeline_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__ */
