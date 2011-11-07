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
    // the filter owns its members!
    boost::unique_lock<boost::shared_mutex> lock(algorithmMutex_);
    boost::unique_lock<boost::shared_mutex> lock2(managerMutex_);
    if(algorithm_)
        delete algorithm_;
    if(manager_)
        delete manager_;
}

void Filter::processRequest(libpipe::Request req, boost::exception_ptr & error)
{
    // forward algorithm handle and request to manager allow only one
    //thread at a time.

    try {
        LIBPIPE_REQUEST_TRACE(req,
            this->getName() + "::processRequest: start.");
        this->getManager()->processRequest(req);
        LIBPIPE_REQUEST_TRACE(req,
            this->getName() + "::processRequest: stop.");
        // this throws segmentation fault????
       // error = boost::exception_ptr();
    } catch (...) {
        error = boost::current_exception();
    }
}

Algorithm* Filter::getAlgorithm() const
{
    boost::shared_lock<boost::shared_mutex> lock(algorithmMutex_);
    return algorithm_;
}

void Filter::setAlgorithm(Algorithm* alg)
{
    boost::unique_lock<boost::shared_mutex> lock(managerMutex_);
    boost::unique_lock<boost::shared_mutex> lock2(algorithmMutex_);
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
    boost::shared_lock<boost::shared_mutex> lock(managerMutex_);

    return manager_;
}

void Filter::setManager(Manager* manager)
{
    boost::unique_lock<boost::shared_mutex> lock(managerMutex_);
    if (manager_ != manager) {
        if (manager_) {
            delete manager_;
        }
        manager_ = manager;
    }
}

std::string Filter::getName() const
{
    boost::shared_lock<boost::shared_mutex> lock(nameMutex_);
    return name_;
}

void Filter::setName(const std::string& name)
{
    boost::unique_lock<boost::shared_mutex> lock(nameMutex_);
    name_ = name;
}

