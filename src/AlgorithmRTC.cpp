/*
 * Algorithm.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 */
#include <libpipe/RTC/AlgorithmRTC.hpp>
#include <cstring> // for memset
#include <sys/time.h> // for gettimeofday
#include <limits>
#include <libpipe/Log.hpp>

#undef LIBPIPE_FILELOG_MAX_LOGGING_LEVEL
#define LIBPIPE_FILELOG_MAX_LOGGING_LEVEL libpipe::logINFO

#include "libpipe/Algorithm.hpp" //for timeval comparisons


using namespace libpipe::rtc;


timeval AlgorithmRTC::initMaxTime()
{
    timeval tv;
    tv.tv_sec = std::numeric_limits<time_t>::max();
    tv.tv_usec = std::numeric_limits<suseconds_t>::max();
    return tv;
}

timeval AlgorithmRTC::initMinTime()
{
    timeval tv;
    tv.tv_sec = std::numeric_limits<time_t>::min();
    tv.tv_usec = std::numeric_limits<suseconds_t>::min();
    return tv;
}

// initialize with maximum value such that any call to update will make the
// instance "younger" than any non-updated instances
const timeval AlgorithmRTC::MAX_TIME = AlgorithmRTC::initMaxTime();

// initialize with minimum value such that any call to update will make the
// instance "older" than any non-updated instances
const timeval AlgorithmRTC::MIN_TIME = AlgorithmRTC::initMinTime();

AlgorithmRTC::AlgorithmRTC() :
    mTime_(AlgorithmRTC::MAX_TIME)
{
}

AlgorithmRTC::~AlgorithmRTC()
{
}

libpipe::Request& AlgorithmRTC::processRequest(libpipe::Request& req)
{
    req = this->update(req);
    if(req.is(libpipe::Request::DELETE)){
        this->setMTime(AlgorithmRTC::MIN_TIME);
    }
    return req;
}

const timeval& AlgorithmRTC::getMTime() const
{
    return mTime_;
}

void AlgorithmRTC::setMTime(const timeval& mTime)
{
    mTime_ = mTime;
}

void AlgorithmRTC::updateMTime()
{
    // use gettimeofday for microsecond resolution
    gettimeofday(&mTime_, NULL);
}

bool AlgorithmRTC::needUpdate() const
{
    /*
     LIBPIPE_LOG(libpipe::logDEBUG) << "Comparing timevals: " << "[" << mTime_.tv_sec << "."
     << mTime_.tv_usec << "] vs. [" << Algorithm::MAX_TIME.tv_sec << "."
     << Algorithm::MAX_TIME.tv_usec;
     */
    return mTime_ == AlgorithmRTC::MAX_TIME;
}


