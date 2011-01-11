/*
 * RequestException.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_PIPELINE_REQUESTEXCEPTION_HPP__
#define __MSTK_INCLUDE_MSTK_PIPELINE_REQUESTEXCEPTION_HPP__

#include <mstk/Exception.hpp>

namespace mstk {

class RequestException : public Exception
{
  public:
    RequestException(const char* msg) : Exception(msg) {}
    
    RequestException(const std::string& msg) : Exception(msg) {}
    
    virtual ~RequestException() throw() {}
};

}

#endif

