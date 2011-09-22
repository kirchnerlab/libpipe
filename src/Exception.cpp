/*
 * Exception.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libpipe/config.hpp>
#include <libpipe/Exception.hpp>

using namespace libpipe;

Exception::Exception(const char* message) :
    msg_(message)
{
}

Exception::Exception(const std::string& message) :
    msg_(message)
{
}

Exception::~Exception() throw ()
{
}

const char* Exception::what() const throw ()
{
    return msg_.c_str();
}

