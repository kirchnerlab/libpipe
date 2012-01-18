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

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/utilities/Exception.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>
#include <libpipe/utilities/Exception.hpp>

#include <limits>
#include <string>

using namespace libpipe::rtc;

timeval Algorithm::initMaxTime()
{
    timeval tv;
    libpipe::utilities::set_max(tv.tv_sec);
    libpipe::utilities::set_max(tv.tv_usec);
    return tv;
}

timeval Algorithm::initMinTime()
{
    timeval tv;
    libpipe::utilities::set_min(tv.tv_sec);
    libpipe::utilities::set_min(tv.tv_usec);
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

void Algorithm::processRequest(libpipe::Request& req)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::mutex> lock(processRequestMutex_);
#endif
    this->update(req);

    if (req.is(libpipe::Request::DELETE)) {
        this->setMTime(Algorithm::MIN_TIME);
    }
}

const timeval& Algorithm::getMTime() const
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(mTimeMutex_);
#endif
    return mTime_;
}

void Algorithm::setMTime(const timeval& mTime)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(mTimeMutex_);
#endif
    mTime_ = mTime;
}

void Algorithm::setParameters(const libpipe::utilities::Parameters& param)
{
    parameters_ = param;
}

void Algorithm::updateMTime()
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(mTimeMutex_);
#endif
    // use gettimeofday for microsecond resolution
    gettimeofday(&mTime_, NULL);
}

bool Algorithm::needUpdate() const
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(mTimeMutex_);
#endif
    return mTime_ == Algorithm::MAX_TIME;
}

boost::shared_ptr<Data> Algorithm::getPort(const std::string& portIdentifier) const
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(portMutex_);
#endif

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

void Algorithm::setInput(const std::string& portIdentifier,
    boost::shared_ptr<Data> dataObject)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(portMutex_);
#endif
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

void Algorithm::connect(Algorithm* alg, const std::string& algPortIdentifier,
    const std::string& thisPortIdentifier)
{
    this->setInput(thisPortIdentifier, alg->getPort(algPortIdentifier));
}

