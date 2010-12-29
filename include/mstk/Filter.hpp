/*
 * Filter.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner 
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_FILTER_HPP__
#define __MSTK_INCLUDE_MSTK_FILTER_HPP__

#include <mstk/config.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

namespace mstk {

class Filter
{
  public:
    virtual ~Filter() = 0;
    virtual void connect(const std::string&, boost::shared_ptr<Filter>, 
      const std::string&) = 0;
};

} // namespace mstk

#endif

