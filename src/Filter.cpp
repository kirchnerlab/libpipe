/*
 * Filter.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#include <mstk/Filter.hpp>
#include <mstk/Manager.hpp>

using namespace mstk;

Filter::~Filter()
{
}

Request& Filter::processRequest(Request& req)
{
    // forward algorithm handle and request to manager
    this->getManager()->processRequest(this->algorithm_, req);
    return req;
}

Filter::AlgorithmPtr Filter::getAlgorithm()
{
    return algorithm_;
}

Filter::ManagerPtr Filter::getManager()
{
    return manager_;
}

void Filter::setAlgorithm(Filter::AlgorithmPtr alg)
{
    algorithm_ = alg;
}

void Filter::setManager(Filter::ManagerPtr manager)
{
    manager_ = manager;
}

