/*
 * Algorithm.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 */
#include <libpipe/rtc/AlgorithmRTC.hpp>

#include <limits>
#include <libpipe/Log.hpp>

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

boost::shared_ptr<LibpipeDataObject> Algorithm::getPort(
    std::string const& portIdentifier) const
{
    std::map<std::string, boost::shared_ptr<LibpipeDataObject> >::const_iterator iter;
    iter = ports_.find(portIdentifier);

    if (iter != ports_.end()) {
        return iter->second;
    } else {
        std::cerr << "unknown type Output "<<portIdentifier << std::endl;
        return boost::shared_ptr<LibpipeDataObject>();
    }
}

void Algorithm::setInput(std::string const& portIdentifier,
    boost::shared_ptr<LibpipeDataObject> dataObject)
{
    std::map<std::string, boost::shared_ptr<LibpipeDataObject> >::iterator iter;
    iter = ports_.find(portIdentifier);

    if (iter != ports_.end()) {
        iter->second = dataObject;
    } else {
        std::cerr << "unknown type Input: "<<portIdentifier << std::endl;
    }
}

void Algorithm::connect(Algorithm* alg, std::string const& inputPortIdentifier,
    std::string const& outputPortIdentifier)
{
    alg->setInput(inputPortIdentifier, this->getPort(outputPortIdentifier));
}

