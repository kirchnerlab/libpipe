/*
 * Config.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */


#include <libpipe/config.hpp>

#include <libpipe/rtc/Config.hpp>

using namespace libpipe::rtc;

Config::~Config(){};

bool PipelineDescriptionLess::operator ()(const PipelineDescription& lhs,
    PipelineDescription& rhs) const
{
    return lhs.requestRank < rhs.requestRank;
}

