/*
 * ModificationTimeManager.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <mstk/pipeline/ModificationTimeManager.hpp>
#include <mstk/pipeline/Filter.hpp>
#include <mstk/algorithm/Algorithm.hpp>
#include <mstk/Log.hpp>

using namespace mstk;

ModificationTimeManager::ModificationTimeManager()
  : SimpleManager() {}

ModificationTimeManager::~ModificationTimeManager() {}

mstk::Request& ModificationTimeManager::processRequest(mstk::Request& req) {
    // make sure we have been set up correctly
    if (!algorithm_) {
        throw RequestException(
          "Cannot process request. No algorithm setup available.");
    }
    // check if we have ever run at all
    bool needUpdate = algorithm_->needUpdate();
    MSTK_LOG(logINFO) << "Need update: " << needUpdate;
    // iterate over all sources and check their modification time
    typedef ManagerSet::iterator MSI;
    for (MSI i = sources_.begin(); i != sources_.end(); ++i) {
        try {
            req = (*i)->processRequest(req);
        } catch (RequestException& e) {
            throw;
        }
        // check the modification time and see if we need to update
        if (!needUpdate && 
          algorithm_->getMTime() <= (*i)->getAlgorithm()->getMTime()) {
            needUpdate = true;
        }
    }
    // update, if necessary
    if (needUpdate) {
        try {
            req = algorithm_->processRequest(req);
        } catch (...) {
            throw RequestException(
              "Cannot process request: algorithm execution caused exception.");
        }
    }
    return req;
}

