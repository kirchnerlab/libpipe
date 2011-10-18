/*
 * LibpipeLoader.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#include "libpipe/rtc/LibpipeLoader.hpp"
#include "libpipe/rtc/LibpipeCreator.hpp"

#include <string>

namespace libpipe {
namespace rtc {

LibpipeLoader::LibpipeLoader(int argc, char *argv[])
{
    std::string filename = "inputFile.txt";
    std::string inputFileHash = "6dc0a277ae36db78b3494d0ddf32dd3d";

    try {
        LibpipeCreator creator_(inputFileHash, filename);
        pipeline_ = creator_.getPipeline();
    } catch (libpipe::Exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

LibpipeLoader::~LibpipeLoader()
{
}

LibpipePipeline LibpipeLoader::getPipeline() const{
    return pipeline_;
}


} /* namespace rtc */
} /* namespace libpipe */
