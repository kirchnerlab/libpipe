/*
 * Manager.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_MANAGER_HPP__
#define __MSTK_INCLUDE_MSTK_MANAGER_HPP__

#include <mstk/config.hpp>
#include <mstk/Request.hpp>

namespace mstk {

class Algorithm;


/** Base class for Managers.
 * Managers are wrapped with Algorithms to form the filters of the pipeline.
 * While the filters provide all data processing capabilities, the managers
 * link the components of the pipeline and make sure that filters get executed
 * in the correct order.
 */
class Manager
{
  public:
    virtual Request& processRequest(Request&) = 0;
    virtual ~Manager() = 0;
};

} // namespace mstk

#endif

