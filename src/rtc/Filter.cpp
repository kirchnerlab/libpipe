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

#include <libpipe/rtc/Filter.hpp>
#include <libpipe/rtc/Manager.hpp>
#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>
#include <libpipe/rtc/ManagerFactory.hpp>
#include <libpipe/rtc/Pipeline.hpp>

using namespace libpipe::rtc;

Filter* Filter::create(const std::string& name,
    const std::string& algorithmName, const std::string& managerName)
{
    Algorithm* a = AlgorithmFactory::instance().createObject(algorithmName);
    Manager* m = ManagerFactory::instance().createObject(managerName);
    m->setAlgorithm(a);
    return new Filter(name, a, m);
}

Filter::Filter(const std::string& name, Algorithm* algorithm, Manager* manager) :
        algorithm_(algorithm), manager_(manager), name_(name)
{
}

Filter::~Filter()
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(algorithmMutex_);
    boost::unique_lock<boost::shared_mutex> lock2(managerMutex_);
#endif
    // the filter owns its members!
    if (algorithm_)
        delete algorithm_;
    if (manager_)
        delete manager_;
}
#ifdef ENABLE_THREADING
void Filter::processThreadedRequest(libpipe::Request req, boost::exception_ptr& error)
{
    try {
        this->processRequest(req);
    } catch (...) {
        /** need to catch exception here, as they need to be handled inside the
         * same thread. They are rethrown later
         */
        error = boost::current_exception();
    }
}
#endif
void Filter::processRequest(libpipe::Request& req)
{
    // forward algorithm handle and request to manager
    LIBPIPE_PIPELINE_TRACE(req, this->getName() + "::processRequest: start.");
    this->getManager()->processRequest(req);
    LIBPIPE_PIPELINE_TRACE(req, this->getName() + "::processRequest: stop.");
}

Algorithm* Filter::getAlgorithm() const
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(algorithmMutex_);
#endif
    return algorithm_;
}

void Filter::setAlgorithm(Algorithm* alg)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(managerMutex_);
    boost::unique_lock<boost::shared_mutex> lock2(algorithmMutex_);
#endif
    if (algorithm_ != alg) {
        if (algorithm_) {
            delete algorithm_;
        }
        algorithm_ = alg;
        if (manager_) {
            manager_->setAlgorithm(alg);
        }
    }
}

Manager* Filter::getManager() const
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(managerMutex_);
#endif
    return manager_;
}

void Filter::setManager(Manager* manager)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(managerMutex_);
#endif
    if (manager_ != manager) {
        if (manager_) {
            delete manager_;
        }
        manager_ = manager;
    }
}

std::string Filter::getName() const
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(nameMutex_);
#endif
    return name_;
}

void Filter::setName(const std::string& name)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(nameMutex_);
#endif
    name_ = name;
}

