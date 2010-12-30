/*
 * Request.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <mstk/pipeline/Request.hpp>

using namespace mstk;

Request::Request(const Request::Type& t)
  : type_(t), trace_(false)
{
}

Request::~Request()
{
}

bool Request::is(const Type& t)
{
    return t == type_;
}

bool Request::getTraceFlag() const
{
    return traceFlag_;
}

void Request::setTraceFlag(const bool tf)
{
    traceFlag_ = tf;
}

void Request::getTrace(std::vector<std::string>& trace)
{
    trace = trace_;
}

void Request::addTrace(const std::string& t)
{
    trace_.push_back(t);
}

void Request::clearTrace()
{
    trace_.clear();
}

