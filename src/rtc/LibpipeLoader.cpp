/*
 * LibpipeLoader.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#include "libpipe/rtc/LibpipeLoader.hpp"
#include "libpipe/rtc/Controler.hpp"

#include <string>
#include <iostream>
#include <fstream>

namespace libpipe {
namespace rtc {

LibpipeLoader::LibpipeLoader(int argc, char *argv[])
{
    std::string filename = "inputFile.txt";

    try {
        Controler creator_(filename);
        pipeline_ = creator_.getPipeline();
    } catch (libpipe::Exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

LibpipeLoader::~LibpipeLoader()
{
}

LibpipePipeline LibpipeLoader::getPipeline() const
{
    return pipeline_;
}


} /* namespace rtc */
} /* namespace libpipe */
