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
#include <boost/shared_ptr.hpp>

namespace mstk {

// forward declarations
class FilterData;

class Algorithm
{
  public:
    virtual ~Algorithm() = 0;
    virtual void addInput(const std::string& meta, 
      boost::shared_ptr<FilterData> inputData);
    virtual boost::shared_ptr<FilterData> getOutput(const std::string& meta);
    virtual void run() = 0;
};

} // namespace mstk

#endif

