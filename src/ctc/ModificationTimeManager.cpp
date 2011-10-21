/*
 * ModificationTimeManager.cpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#include <libpipe/ctc/ModificationTimeManager.hpp>
#include <libpipe/ctc/Filter.hpp>
#include <libpipe/ctc/Algorithm.hpp>
#include <libpipe/utilities/Log.hpp>

using namespace libpipe::ctc;

ModificationTimeManager::ModificationTimeManager() :
    Manager()
{
}

ModificationTimeManager::~ModificationTimeManager()
{
}

libpipe::Request& ModificationTimeManager::processRequest(
    Request& req)
{
    // make sure we have been set up correctly
    if (!algorithm_) {
        throw RequestException(
            "Cannot process request. No algorithm setup available.");
    }
    // check if we have ever run at all
    bool needUpdate = algorithm_->needUpdate();
    // iterate over all sources and check their modification time
    typedef FilterSet::iterator FSI;
    for (FSI i = sources_.begin(); i != sources_.end(); ++i) {
        try {
            req = (*i)->processRequest(req);
        } catch (RequestException& e) {
            throw;
        }
        // check the modification time and see if we need to update
        if (!needUpdate && algorithm_->getMTime()
                <= (*i)->getAlgorithm()->getMTime()) {
            needUpdate = true;
        }
    }
    // update, if necessary
    if (needUpdate) {
        try {
            req = algorithm_->processRequest(req);
        } catch (std::exception& e) {
            std::string str(e.what());
            throw RequestException(
                "ModificationTimeManager.cpp: Cannot process request: algorithm execution caused exception: "
                        + str);
        } catch (...) {
            throw RequestException(
                "ModificationTimeManager.cpp: Cannot process request: algorithm execution caused exception.");
        }
    }
    return req;
}

