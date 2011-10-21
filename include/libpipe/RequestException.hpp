/*
 * RequestException.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_PIPELINE_REQUESTEXCEPTION_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_PIPELINE_REQUESTEXCEPTION_HPP__

#include <libpipe/config.hpp>

#include <libpipe/utilities/Exception.hpp>

namespace libpipe {

class RequestException : public utilities::Exception
{
public:
    RequestException(const char* msg) :
        Exception(msg)
    {
    }

    RequestException(const std::string& msg) :
        Exception(msg)
    {
    }

    virtual ~RequestException() throw ()
    {
    }
};

}

#endif

