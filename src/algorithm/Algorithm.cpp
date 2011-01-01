/*
 * Algorithm.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <mstk/algorithm/Algorithm.hpp>
#include <cstring> // for memset
#include <sys/time.h> // for gettimeofday

bool operator<(const timeval& lhs, const timeval& rhs)
{
    if (lhs.tv_sec < rhs.tv_sec ||
      ( lhs.tv_sec == rhs.tv_sec && lhs.tv_usec < rhs.tv_usec )) {
        return true;
    }
    return false;
}

using namespace mstk;

Algorithm::Algorithm()
{
    memset(static_cast<void*>(&mTime_), 0, sizeof(timeval));
}

Algorithm::~Algorithm()
{}

Request& Algorithm::processRequest(Request& req) {
    if (req.is(Request::UPDATE)) {
        req = this->update(req);
    }
    return req;
}


const timeval& Algorithm::getMTime() const
{
    return mTime_;
}

void Algorithm::setMTime(const timeval& mTime)
{
    mTime_	= mTime;
}

void Algorithm::updateMTime()
{
    // use gettimeofday for microsecond resolution
    gettimeofday(&mTime_, NULL);
}
