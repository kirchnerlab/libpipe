/*
 * Loader.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__

#include "libpipe/rtc/Pipeline.hpp"

namespace libpipe {
namespace rtc {


class Loader
{
    public:
        Loader(int argc, char *argv[]);
        ~Loader();

        Pipeline getPipeline() const;

    private:
        Pipeline pipeline_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__ */
