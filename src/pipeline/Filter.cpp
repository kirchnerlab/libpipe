/*
 * Filter.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <mstk/pipeline/Filter.hpp>
#include <mstk/algorithm/Algorithm.hpp>
#include <mstk/pipeline/Manager.hpp>

using namespace mstk;

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
    MSTK_REQUEST_TRACE(req, this->getName() + ":Filter::processRequest: start.");
    this->getManager()->processRequest(req);
    MSTK_REQUEST_TRACE(req, this->getName() + ":Filter::processRequest: stop.");
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

