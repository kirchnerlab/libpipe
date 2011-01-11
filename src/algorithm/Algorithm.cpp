/*
 * Algorithm.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <libpipe/algorithm/Algorithm.hpp>
#include <cstring> // for memset
#include <sys/time.h> // for gettimeofday
#include <limits>
#include <libpipe/Log.hpp>

#undef LIBPIPE_FILELOG_MAX_LOGGING_LEVEL
#define LIBPIPE_FILELOG_MAX_LOGGING_LEVEL libpipe::logINFO

bool operator<=(const timeval& lhs, const timeval& rhs)
{
    if (lhs.tv_sec < rhs.tv_sec ||
      ( lhs.tv_sec == rhs.tv_sec && lhs.tv_usec <= rhs.tv_usec )) {
        return true;
    }
    return false;
}

bool operator==(const timeval& lhs, const timeval& rhs)
{
    if (lhs.tv_sec == rhs.tv_sec && lhs.tv_usec == rhs.tv_usec )
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const timeval& tv)
{
    os << tv.tv_sec << "." << tv.tv_usec;
    return os;
}

using namespace libpipe;

timeval Algorithm::initMaxTime()
{
    timeval tv;
    tv.tv_sec = std::numeric_limits<time_t>::max();
    tv.tv_usec = std::numeric_limits<suseconds_t>::max();
    return tv;
}

// initialize with maximum value such that any call to update will make the
// instance "younger" than any non-updated instances
const timeval Algorithm::MAX_TIME = Algorithm::initMaxTime();

Algorithm::Algorithm() : mTime_(Algorithm::MAX_TIME)
{}

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

bool Algorithm::needUpdate() const
{
    /*
    LIBPIPE_LOG(libpipe::logDEBUG) << "Comparing timevals: " << "[" << mTime_.tv_sec << "." 
      << mTime_.tv_usec << "] vs. [" << Algorithm::MAX_TIME.tv_sec << "."
      << Algorithm::MAX_TIME.tv_usec;
    */
    return mTime_ == Algorithm::MAX_TIME;
}
