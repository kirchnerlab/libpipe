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
#include <vector>

namespace mstk {

class Filter;

class Manager
{
  public:
    virtual void update() = 0;
    virtual ~Manager() = 0;
};

} // namespace mstk

#endif

