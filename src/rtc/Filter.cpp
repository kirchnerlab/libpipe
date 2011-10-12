/*
 * Filter.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */
#include <libpipe/rtc/Filter.hpp>
#include <libpipe/rtc/Manager.hpp>
#include <libpipe/rtc/Algorithm.hpp>

#include <libpipe/rtc/LibpipeFactories.hpp>

using namespace libpipe::rtc;


Filter* Filter::create(const std::string& name,
    const std::string& algorithmName, const std::string& managerName)
{
    Algorithm* a = AlgorithmFactory::instance().createObject(
        algorithmName);
    Manager* m = ManagerFactory::instance().createObject(
        managerName);
    m->setAlgorithm(a);
    return new Filter(name, a, m);
}

Filter::Filter(const std::string& name, Algorithm* algorithm,
    Manager* manager) :
        algorithm_(algorithm),  manager_(manager) , name_(name)
{
}

Filter::~Filter()
{
    // the filter owns its members!
    delete algorithm_;
    delete manager_;
}

libpipe::Request& Filter::processRequest(libpipe::Request& req)
{
    // forward algorithm handle and request to manager
    LIBPIPE_REQUEST_TRACE(req, this->getName() + "::processRequest: start.");
    this->getManager()->processRequest(req);
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

