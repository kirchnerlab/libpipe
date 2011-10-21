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

