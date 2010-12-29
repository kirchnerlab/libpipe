/*
 * Filter.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <mstk/Filter.hpp>
#include <mstk/Algorithm.hpp>
#include <mstk/Manager.hpp>

using namespace mstk;

Filter::Filter() : algorithm_(0), manager_(0) {}

Filter::~Filter()
{
    delete algorithm_;
    delete manager_;
}

Request& Filter::processRequest(Request& req)
{
    // forward algorithm handle and request to manager
    this->getManager()->processRequest(req);
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

