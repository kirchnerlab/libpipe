/*
 * Algorithm.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_ALGORITHM_HPP__
#define __MSTK_INCLUDE_MSTK_ALGORITHM_HPP__

#include <mstk/config.hpp>

namespace mstk {

class Algorithm
{
  public:
    virtual ~Algorithm() = 0;
    virtual void run() = 0;
};

} // namespace mstk

#endif

