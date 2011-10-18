/*
 * LibpipeLoader.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#include "libpipe/rtc/LibpipeLoader.hpp"
#include "libpipe/rtc/LibpipeCreator.hpp"

#include <string>
#include <iostream>
#include <fstream>

namespace libpipe {
namespace rtc {

LibpipeLoader::LibpipeLoader(int argc, char *argv[])
{
    std::string filename = "inputFile.txt";
    std::string inputFileHash = this->getHash(filename);

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

LibpipePipeline LibpipeLoader::getPipeline() const
{
    return pipeline_;
}

std::string LibpipeLoader::getHash(std::string const& filename) const
{
    std::fstream filestr;

    filestr.open(filename.c_str(), std::fstream::in);

    char name[256];
    std::string returnValue;
    filestr.getline(name, 256);
    returnValue = name;
    returnValue.erase(0, 1);
    filestr.close();
    return returnValue;

}

} /* namespace rtc */
} /* namespace libpipe */
