/*
 * Algorithm.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_ALGORITHM_HPP__
#define __MSTK_INCLUDE_MSTK_ALGORITHM_HPP__

#include <mstk/config.hpp>

#include <string>
#include <map>
#include <mstk/Request.hpp>

namespace mstk {


/** Base class for all MSTK algorithms.
 */
class Algorithm
{
  public:
    /** Pure virtual descructor.
     */
    virtual ~Algorithm() = 0;
    
    /** Processes the current request.
     * Derived classes should run the algorithm upon this method being called.
     */
    virtual Request& processRequest(Request& req) = 0;

  protected:
};

} // namespace mstk

#endif

