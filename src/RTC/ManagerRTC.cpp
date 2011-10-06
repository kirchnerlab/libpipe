/*
 * Manager.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */
#include <libpipe/RTC/ManagerRTC.hpp>
#include <libpipe/RTC/FilterRTC.hpp>
#include <libpipe/RTC/AlgorithmRTC.hpp>

using namespace libpipe_rtc;

ManagerRTC::ManagerRTC() :
        algorithm_(0)
{
}

ManagerRTC::~ManagerRTC()
{
}

AlgorithmRTC* ManagerRTC::getAlgorithm()
{
    return algorithm_;
}

void ManagerRTC::setAlgorithm(AlgorithmRTC* alg)
{
    // the manager does not own the
    // algorithm object. Hence, just move the pointer.
    algorithm_ = alg;
}

libpipe::Request& ManagerRTC::processRequest(libpipe::Request& req)
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

void ManagerRTC::connect(boost::shared_ptr<FilterRTC> f)
{
    sources_.insert(f);
}

void ManagerRTC::disconnect()
{
    sources_.clear();
}

const bool ManagerRTC::registered_ = registerLoader();

