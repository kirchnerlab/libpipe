/*
 * SimpleManager.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <libpipe/pipeline/SimpleManager.hpp>
#include <libpipe/pipeline/Filter.hpp>
#include <libpipe/algorithm/Algorithm.hpp>

using namespace libpipe;

SimpleManager::SimpleManager() : algorithm_(0) {}

SimpleManager::~SimpleManager() {}

void SimpleManager::setAlgorithm(libpipe::Algorithm* alg) 
{
    algorithm_ = alg;
}

libpipe::Request& SimpleManager::processRequest(libpipe::Request& req) {
    if (!algorithm_) {
        throw RequestException(
          "Cannot process request. No algorithm setup available.");
    }
    typedef ManagerSet::iterator MSI;
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
    } catch (...) {
        throw RequestException(
          "Cannot process request: algorithm execution caused exception.");
    }
    return req;
}

void SimpleManager::connect(Filter* sm) {
    sources_.insert(sm);
}

