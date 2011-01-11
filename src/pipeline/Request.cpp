/*
 * Request.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <libpipe/pipeline/Request.hpp>

using namespace libpipe;

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
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    static char buffer[40];
    strftime(buffer, 40, "%Y.%m.%d:%H:%M:%S %Z ", timeinfo);
    trace_.push_back(std::string(buffer) + t);
}

void Request::clearTrace()
{
    trace_.clear();
}

