/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2010 Marc Kirchner
*
* This file is part of libpipe.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include <libpipe/config.hpp>
#include <libpipe/Request.hpp>

using namespace libpipe;

Request::Request(const Request::Type& t) :
        type_(t), traceFlag_(false)
{
}

Request::~Request()
{
}

bool Request::is(const Type& t)
{
    return t == type_;
}

Request::Type Request::getType() const
{
    return type_;
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

Request::Request& Request::operator+=(Request const& rhs){
    if(this->traceFlag_==rhs.traceFlag_ and this->type_==rhs.type_){
        trace_.insert( trace_.end(), rhs.trace_.begin(), rhs.trace_.end() );
    }
    return this;
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

