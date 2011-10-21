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
#include <libpipe/ctc/Manager.hpp>
#include <libpipe/ctc/Filter.hpp>
#include <libpipe/ctc/Algorithm.hpp>

using namespace libpipe::ctc;

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

libpipe::Request& Manager::processRequest(Request& req)
{
    if (req.is(Request::UPDATE)) {
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
                "ModificationTimeManager: Cannot process request: algorithm execution caused exception: "
                        + str);
        } catch (...) {
            throw RequestException(
                "ModificationTimeManager: Cannot process request: algorithm execution caused exception.");
        }
    } else if (req.is(Request::DELETE)) {
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

