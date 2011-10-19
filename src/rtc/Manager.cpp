/*
 * Manager.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */
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
    return algorithm_;
}

void Manager::setAlgorithm(Algorithm* alg)
{
    // the manager does not own the
    // algorithm object. Hence, just move the pointer.
    algorithm_ = alg;
}

libpipe::Request& Manager::processRequest(libpipe::Request& req)
{
    if (req.is(libpipe::Request::UPDATE)) {
        if (!algorithm_) {
            throw libpipe::RequestException(
                "Cannot process request. No algorithm setup available.");
        }
        typedef FilterSet::iterator MSI;
        // iterate over all sources
        for (MSI i = sources_.begin(); i != sources_.end(); ++i) {
            try {
                req = (*i)->processRequest(req);
            } catch (libpipe::RequestException& e) {
                throw;
            }
        }
        try {
            req = algorithm_->processRequest(req);
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
        req = algorithm_->processRequest(req);
        this->disconnect();
    }
    return req;
}

void Manager::connect(boost::shared_ptr<Filter> f)
{
    sources_.insert(f);
}

void Manager::disconnect()
{
    sources_.clear();
}

const bool Manager::registerLoader()
{
    std::string ids = "MangerRTC";
    return ManagerFactory::instance().registerType(ids, Manager::create);
}

std::set<boost::shared_ptr<Filter> > Manager::getSources()
{
    return sources_;
}

const bool Manager::registered_ = registerLoader();

