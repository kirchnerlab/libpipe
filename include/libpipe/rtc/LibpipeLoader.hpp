/*
 * LibpipeLoader.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPELOADER_HPP_
#define LIBPIPELOADER_HPP_

#include "libpipe/rtc/LibpipePipeline.hpp"

namespace libpipe {
namespace rtc {


class LibpipeLoader
{
    public:
        LibpipeLoader(int argc, char *argv[]);
        ~LibpipeLoader();

        LibpipePipeline getPipeline() const;

    private:
        LibpipePipeline pipeline_;

        std::string getHash(std::string const& filename) const;
};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* LIBPIPELOADER_HPP_ */
