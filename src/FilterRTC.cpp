/*
 * Filter.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */
#include <libpipe/RTC/FilterRTC.hpp>
#include <libpipe/RTC/ManagerRTC.hpp>
#include <libpipe/RTC/AlgorithmRTC.hpp>

#include <libpipe/RTC/LibpipeFactories.hpp>

using namespace libpipe::rtc;


Filter* Filter::create(const std::string& name,
    const std::string& algorithmName, const std::string& managerName)
{
    Algorithm* a = AlgorithmFactory::instance().createObject(
        algorithmName);
    ManagerRTC* m = ManagerFactory::instance().createObject(
        managerName);
    return new Filter(name, a, m);
}

Filter::Filter(const std::string& name, Algorithm* algorithm,
    ManagerRTC* manager) :
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

ManagerRTC* Filter::getManager()
{
    return manager_;
}

void Filter::setManager(ManagerRTC* manager)
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

