/*
 * Filter.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <libpipe/pipeline/Filter.hpp>
#include <libpipe/algorithm/Algorithm.hpp>
#include <libpipe/pipeline/Manager.hpp>

using namespace libpipe;

Filter::Filter(const std::string& name) 
  : algorithm_(0), manager_(0), name_(name) 
{}

Filter::~Filter()
{
    delete algorithm_;
    delete manager_;
}

Request& Filter::processRequest(Request& req)
{
    // forward algorithm handle and request to manager
    LIBPIPE_REQUEST_TRACE(req, this->getName() + "::processRequest: start.");
    this->getManager()->processRequest(req);
    LIBPIPE_REQUEST_TRACE(req,  this->getName() + "::processRequest: stop.");
    return req;
}

void Filter::setAlgorithm(Algorithm* alg)
{
    algorithm_ = alg;
}

void Filter::setManager(Manager* manager)
{
    manager_ = manager;
}

std::string Filter::getName() const
{
    return name_;
}

