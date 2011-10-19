/*
 * Algorithm.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 */
#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/Exception.hpp>

#include <limits>
#include <libpipe/Log.hpp>
#include <string>

#undef LIBPIPE_FILELOG_MAX_LOGGING_LEVEL
#define LIBPIPE_FILELOG_MAX_LOGGING_LEVEL libpipe::logINFO

#include "libpipe/Algorithm.hpp" //for timeval comparisons
using namespace libpipe::rtc;

timeval Algorithm::initMaxTime()
{
    timeval tv;
    tv.tv_sec = std::numeric_limits<time_t>::max();
    tv.tv_usec = std::numeric_limits<suseconds_t>::max();
    return tv;
}

timeval Algorithm::initMinTime()
{
    timeval tv;
    tv.tv_sec = std::numeric_limits<time_t>::min();
    tv.tv_usec = std::numeric_limits<suseconds_t>::min();
    return tv;
}

// initialize with maximum value such that any call to update will make the
// instance "younger" than any non-updated instances
const timeval Algorithm::MAX_TIME = Algorithm::initMaxTime();

// initialize with minimum value such that any call to update will make the
// instance "older" than any non-updated instances
const timeval Algorithm::MIN_TIME = Algorithm::initMinTime();

Algorithm::Algorithm() :
        mTime_(Algorithm::MAX_TIME)
{
}

Algorithm::~Algorithm()
{
}

libpipe::Request& Algorithm::processRequest(libpipe::Request& req)
{
    req = this->update(req);
    if (req.is(libpipe::Request::DELETE)) {
        this->setMTime(Algorithm::MIN_TIME);
    }
    return req;
}

const timeval& Algorithm::getMTime() const
{
    return mTime_;
}

void Algorithm::setMTime(const timeval& mTime)
{
    mTime_ = mTime;
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

boost::shared_ptr<Data> Algorithm::getPort(
    std::string const& portIdentifier) const
{
    std::map<std::string, boost::shared_ptr<Data> >::const_iterator iter;
    iter = ports_.find(portIdentifier);

    if (iter != ports_.end()) {
        return iter->second;
    } else {
        std::string message =
                "Algorithm::getPort failed, the following port was not registered: ";
        message += portIdentifier;
        libpipe_fail(message);
    }
}

void Algorithm::setInput(std::string const& portIdentifier,
    boost::shared_ptr<Data> dataObject)
{
    std::map<std::string, boost::shared_ptr<Data> >::iterator iter;
    iter = ports_.find(portIdentifier);

    if (iter != ports_.end()) {
        iter->second = dataObject;
    } else {
        std::string message =
                "Algorithm::setInput failed, the following port was not registered: ";
        message += portIdentifier;
        libpipe_fail(message);
    }
}

void Algorithm::connect(Algorithm* alg, std::string const& algPortIdentifier,
    std::string const& thisPortIdentifier)
{
    this->setInput(thisPortIdentifier, alg->getPort(algPortIdentifier));
}

