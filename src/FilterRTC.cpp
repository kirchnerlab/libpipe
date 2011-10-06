/*
 * Filter.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */
#include <libpipe/FilterRTC.hpp>
#include <libpipe/AlgorithmRTC.hpp>
#include <libpipe/ManagerRTC.hpp>

using namespace libpipe_rtc;

static FilterRTC* FilterRTC::create(const std::string& name, const std::string& algorithmName,
    const std::string& managerName){
    return new FilterRTC(name, algorithmName, managerName);
}

FilterRTC::FilterRTC(const std::string& name, const std::string& algorithmName,
    const std::string& managerName)
{
    AlgorithmRTC* a = libpipe_rtc::AlgorithmFactory::instance().createObject(algorithmName);
    ManagerRTC* m = libpipe_rtc::ManagerFactory::instance().createObject(managerName);
    this->setManager(m);
    this->setAlgorithm(a);
}

FilterRTC::~FilterRTC()
{
    // the filter owns its members!
    delete algorithm_;
    delete manager_;
}

libpipe::Request& FilterRTC::processRequest(libpipe::Request& req)
{
    // forward algorithm handle and request to manager
    LIBPIPE_REQUEST_TRACE(req, this->getName() + "::processRequest: start.");
    this->getManager()->processRequest(req);
    LIBPIPE_REQUEST_TRACE(req, this->getName() + "::processRequest: stop.");
    return req;
}

AlgorithmRTC* FilterRTC::getAlgorithm()
{
    return algorithm_;
}

void FilterRTC::setAlgorithm(AlgorithmRTC* alg)
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

ManagerRTC* FilterRTC::getManager()
{
    return manager_;
}

void FilterRTC::setManager(ManagerRTC* manager)
{
    if (manager_ != manager) {
        if (manager_) {
            delete manager_;
        }
        manager_ = manager;
    }
}

std::string FilterRTC::getName() const
{
    return name_;
}

void FilterRTC::setName(const std::string& name)
{
    name_ = name;
}

