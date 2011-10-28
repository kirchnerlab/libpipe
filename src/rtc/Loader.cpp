/*
 * Loader.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */
#include <libpipe/config.hpp>

#include <libpipe/rtc/Loader.hpp>
#include <libpipe/rtc/Controler.hpp>
#include <libpipe/utilities/Exception.hpp>

#include <string>
#include <iostream>
#include <fstream>

namespace libpipe {
namespace rtc {

Loader::Loader(const std::map<std::string, std::string>& filename)
{
    try {
        Controler creator_(filename);
        pipeline_ = creator_.getPipeline();
    } catch (utilities::Exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

Loader::~Loader()
{
}

Pipeline Loader::getPipeline() const
{
    return pipeline_;
}

} /* namespace rtc */
} /* namespace libpipe */
