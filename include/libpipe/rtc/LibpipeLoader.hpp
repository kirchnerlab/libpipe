/*
 * LibpipeLoader.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPELOADER_HPP_
#define LIBPIPELOADER_HPP_

#include "libpipe/rtc/Pipeline.hpp"

namespace libpipe {
namespace rtc {


class LibpipeLoader
{
    public:
        LibpipeLoader(int argc, char *argv[]);
        ~LibpipeLoader();

        Pipeline getPipeline() const;

    private:
        Pipeline pipeline_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* LIBPIPELOADER_HPP_ */
