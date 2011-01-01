/*
 * SimpleManager.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <mstk/pipeline/SimpleManager.hpp>
#include <mstk/pipeline/Filter.hpp>
#include <mstk/algorithm/Algorithm.hpp>

using namespace mstk;

SimpleManager::SimpleManager() {}

SimpleManager::~SimpleManager() {}

void SimpleManager::setAlgorithm(mstk::Algorithm* alg) 
{
    algorithm_ = alg;
}

mstk::Request& SimpleManager::processRequest(mstk::Request& req) {
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

