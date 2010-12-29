/*
 * Manager.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_MANAGER_HPP__
#define __MSTK_INCLUDE_MSTK_MANAGER_HPP__

#include <mstk/config.hpp>
#include <boost/shared_ptr.hpp>
#include <mstk/Request.hpp>

namespace mstk {

class Algorithm;

class Manager
{
  public:
    typedef boost::shared_ptr<Algorithm> AlgorithmPtr;
    virtual void processRequest(AlgorithmPtr, Request&) = 0;
    virtual ~Manager() = 0;
};

} // namespace mstk

#endif

