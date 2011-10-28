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
#include <map>

namespace libpipe {
namespace rtc {


class Loader
{
    public:
        /** Constructor
         * @param filename Name of the input files. With a key.
         */
        Loader(const std::map<std::string, std::string>& filename);
        /**
         * Destructor
         */
        ~Loader();

        /**
         * Returns the pipeline object
         * @return A pipeline Object
         */
        Pipeline getPipeline() const;

    private:
        /**
         * The pipeline Object
         */
        Pipeline pipeline_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__ */
