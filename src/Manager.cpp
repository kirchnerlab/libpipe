/*
 * Manager.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <libpipe/Manager.hpp>
#include <libpipe/Filter.hpp>
#include <libpipe/Algorithm.hpp>

using namespace libpipe;

Manager::Manager() : algorithm_(0) {}

Manager::~Manager() {}

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

Request& Manager::processRequest(Request& req) {
    if (!algorithm_) {
        throw RequestException(
          "Cannot process request. No algorithm setup available.");
    }
    typedef FilterSet::iterator MSI;
    // iterate over all sources
    for (MSI i = sources_.begin(); i != sources_.end(); ++i) {
        try {
            req = (*i)->processRequest(req);
        } catch (RequestException& e) {
            throw;
        }
    }
    try {
        req = algorithm_->processRequest(req);
    } catch (std::exception& e) {
        std::string str(e.what());
        throw RequestException(
          "ModificationTimeManager: Cannot process request: algorithm execution caused exception: " + str);
    } catch (...) {
        throw RequestException(
          "ModificationTimeManager: Cannot process request: algorithm execution caused exception.");
    }
    return req;
}

void Manager::connect(Filter* f) {
    sources_.insert(f);
}

