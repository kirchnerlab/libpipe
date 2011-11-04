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

#include <libpipe/rtc/Manager.hpp>
#include <libpipe/rtc/Filter.hpp>
#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/ManagerFactory.hpp>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace libpipe::rtc;

Manager* Manager::create()
{
    return new Manager;
}

Manager::Manager() :
        algorithm_(0)
{
}

Manager::~Manager()
{
}

Algorithm* Manager::getAlgorithm()
{
    boost::shared_lock<boost::shared_mutex> lock(algorithmMutex_);
    return algorithm_;
}

void Manager::setAlgorithm(Algorithm* alg)
{
    // the manager does not own the
    // algorithm object. Hence, just move the pointer.
    boost::unique_lock<boost::shared_mutex> lock(algorithmMutex_);
    algorithm_ = alg;
}

void Manager::processRequest(libpipe::Request req)
{
    boost::unique_lock<boost::mutex> lock(processRequestMutex_);
    if (req.is(libpipe::Request::UPDATE)) {
        if (!algorithm_) {
            throw libpipe::RequestException(
                "Cannot process request. No algorithm setup available.");
        }
        typedef FilterSet::iterator MSI;
        // iterate over all sources

        boost::thread_group thread;
        std::vector<boost::exception_ptr> error;
        for (MSI i = sources_.begin(); i != sources_.end(); ++i) {
            try {
#ifdef ENABLE_THREADING
                error.push_back(boost::exception_ptr());
                thread.add_thread(
                    new boost::thread(&Filter::processRequest, (*i), req,
                        boost::ref(error.back())));
#else
                (*i)->processRequest(req);
#endif
            } catch (libpipe::RequestException& e) {
                throw;
            }
        }
#ifdef ENABLE_THREADING
        thread.join_all();
        for (std::vector<boost::exception_ptr>::iterator it = error.begin();
                it != error.end(); it++) {
            if ((*it))
                boost::rethrow_exception((*it));
        }

#endif

        try {
            algorithm_->processRequest(req);
        } catch (std::exception& e) {
            std::string str(e.what());
            throw libpipe::RequestException(
                "ModificationTimeManager: Cannot process request: algorithm execution caused exception: "
                        + str);
        } catch (...) {
            throw libpipe::RequestException(
                "ModificationTimeManager: Cannot process request: algorithm execution caused exception.");
        }
    } else if (req.is(libpipe::Request::DELETE)) {
        algorithm_->processRequest(req);
        this->disconnect();
    }
}

void Manager::connect(boost::shared_ptr<Filter> f)
{
    boost::unique_lock<boost::shared_mutex> lock(sourcesMutex_);
    sources_.insert(f);
}

void Manager::disconnect()
{
    boost::unique_lock<boost::shared_mutex> lock(sourcesMutex_);
    sources_.clear();
}

std::set<boost::shared_ptr<Filter> > Manager::getSources()
{
    boost::shared_lock<boost::shared_mutex> lock(sourcesMutex_);
    return sources_;
}

const bool Manager::registerLoader()
{
    std::string ids = "MangerRTC";
    return ManagerFactory::instance().registerType(ids, Manager::create);
}



const bool Manager::registered_ = registerLoader();

