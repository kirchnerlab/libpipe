/*
 * Loader.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LOADER_HPP_
#define LOADER_HPP_

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
#endif /* LIBPIPELOADER_HPP_ */
