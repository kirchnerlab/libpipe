/*
 * PortInformation.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <mstk/PortInformation.hpp>

using namespace mstk;

bool PortInformation::is_compatible::operator()(
  const PortInformation& outPortInfo, const PortInformation& inPortInfo)
{
    return outPortInfo.getType() == inPortInfo.getType();
}

PortInformation::PortInformation()
  : type_()
{
}

PortInformation::~PortInformation()
{
}

std::string PortInformation::getName() const
{
    return name_;
}

void PortInformation::setName(const std::string& name)
{
    name_ = name;
}

PortInformation::Type PortInformation::getType() const
{
    return type_;
}

void PortInformation::setType(const Type& t)
{
    type_ = t;
}

