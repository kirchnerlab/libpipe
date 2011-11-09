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
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(algorithmMutex_);
#endif
    return algorithm_;
}

void Manager::setAlgorithm(Algorithm* alg)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(algorithmMutex_);
#endif
    // the manager does not own the
    // algorithm object. Hence, just move the pointer.
    algorithm_ = alg;
}

void Manager::processRequest(libpipe::Request& req)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::mutex> lock(processRequestMutex_);
#endif
    if (req.is(libpipe::Request::UPDATE)) {
        if (!algorithm_) {
            throw boost::enable_current_exception(
                libpipe::RequestException(
                    "Cannot process request. No algorithm instance available."));
        }
#ifdef ENABLE_THREADING
        boost::thread_group thread;
        boost::unique_lock<boost::shared_mutex> lockSources(sourcesMutex_);
        // catch errors, to rethrow the exceptions
        std::vector<boost::exception_ptr> error(sources_.size());
        std::vector<boost::exception_ptr>::iterator errorIt = error.begin();
#endif
        typedef FilterSet::iterator MSI;
        // iterate over all sources
        for (MSI i = sources_.begin(); i != sources_.end(); ++i) {
#ifdef ENABLE_THREADING
            thread.add_thread(
                new boost::thread(&Filter::processThreadedRequest, (*i), req,
                    boost::ref(*errorIt)));
            errorIt++;
#else
            try {
                (*i)->processRequest(req);
            } catch (libpipe::RequestException& e) {
                throw boost::enable_current_exception(e);
            }
#endif

        }
#ifdef ENABLE_THREADING
        thread.join_all();
        //rethrow all exceptions
        for (std::vector<boost::exception_ptr>::iterator it = error.begin();
                it != error.end(); it++) {
            if ((*it))
                boost::rethrow_exception((*it));
        }
#endif
    }
    try {
        algorithm_->processRequest(req);
    } catch (std::exception& e) {
        std::string str(e.what());
        throw boost::enable_current_exception(
            libpipe::RequestException(
                "ModificationTimeManager: Cannot process request: algorithm execution caused exception: "
                        + str));
    } catch (...) {
        throw boost::enable_current_exception(
            libpipe::RequestException(
                "ModificationTimeManager: Cannot process request: algorithm execution caused exception."));
    }
    if (req.is(libpipe::Request::DELETE)) {
        this->disconnect();
    }
}

void Manager::connect(boost::shared_ptr<Filter> f)
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(sourcesMutex_);
#endif
    sources_.insert(f);
}

void Manager::disconnect()
{
#ifdef ENABLE_THREADING
    boost::unique_lock<boost::shared_mutex> lock(sourcesMutex_);
#endif
    sources_.clear();
}

std::set<boost::shared_ptr<Filter> > Manager::getSources()
{
#ifdef ENABLE_THREADING
    boost::shared_lock<boost::shared_mutex> lock(sourcesMutex_);
#endif
    return sources_;
}

const bool Manager::registerLoader()
{
    std::string ids = "MangerRTC";
    return ManagerFactory::instance().registerType(ids, Manager::create);
}

const bool Manager::registered_ = registerLoader();

