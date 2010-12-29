/*
 * Algorithm.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <mstk/Algorithm.hpp>

using namespace mstk;

Algorithm::~Algorithm()
{
}

Algorithm::PortInformationMap Algorithm::getInputPortInformation() const
{
    return inputPortInformation_;
}

Algorithm::PortInformationMap Algorithm::getOutputPortInformation() const
{
    return outputPortInformation_;
}

void Algorithm::addInputPortInformation(const PortInformation& pInfo)
{
    inputPortInformation_[pInfo.getName()] = pInfo;
}

void Algorithm::addOutputPortInformation(const PortInformation& pInfo)
{
    outputPortInformation_[pInfo.getName()] = pInfo;
}
