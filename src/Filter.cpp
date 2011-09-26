/*
 * Filter.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <libpipe/Filter.hpp>
#include <libpipe/Algorithm.hpp>
#include <libpipe/Manager.hpp>

using namespace libpipe;

Filter::Filter(const std::string& name) :
    algorithm_(0), manager_(0), name_(name)
{
}

Filter::~Filter()
{
    // the filter owns its members!
    delete algorithm_;
    delete manager_;
}

Request& Filter::processRequest(Request& req)
{
    LIBPIPE_REQUEST_TRACE(req, this->getName() + "::processRequest: start.");
    if(req.is(Request::UPDATE)){
        // forward algorithm handle and request to manager
        this->getManager()->processRequest(req);
    }
    else if(req.is(Request::DELETE)){
        this->getManager()->disconnect();
    }
    else{
        throw RequestException (
            "Filter: Cannot process request: request type is unknown: "
                    + req.getType());
    }
    LIBPIPE_REQUEST_TRACE(req, this->getName() + "::processRequest: stop.");
    return req;
}

Algorithm* Filter::getAlgorithm()
{
    return algorithm_;
}

void Filter::setAlgorithm(Algorithm* alg)
{
    if (algorithm_ != alg) {
        if (algorithm_) {
            delete algorithm_;
        }
        algorithm_ = alg;
        if (manager_) {
            manager_->setAlgorithm(alg);
        }
    }
}

Manager* Filter::getManager()
{
    return manager_;
}

void Filter::setManager(Manager* manager)
{
    if (manager_ != manager) {
        if (manager_) {
            delete manager_;
        }
        manager_ = manager;
    }
}

std::string Filter::getName() const
{
    return name_;
}

void Filter::setName(const std::string& name)
{
    name_ = name;
}

