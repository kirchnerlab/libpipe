/*
 * SimpleManager.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <mstk/SimpleManager.hpp>

using namespace mstk;

SimpleManager::SimpleManager() {}

SimpleManager::~SimpleManager() {}

void SimpleManager::setAlgorithm(mstk::Algorithm* alg) 
{
    algorithm_ = alg;
}

mstk::Request& SimpleManager::processRequest(mstk::Request& req) {
    typedef ManagerSet::iterator MSI;
    // iterate over all sources
    for (MSI i = sources_.begin(); i != sources_.end(); ++i) {
        req = (*i)->processRequest(req);
    }
    req = algorithm_->processRequest(req);
    return req;
}

void SimpleManager::connect(SimpleManager* sm) {
    sources_.insert(sm);
}

