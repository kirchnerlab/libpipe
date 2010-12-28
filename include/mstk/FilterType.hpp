/*
 * FilterType.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner 
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_FILTERTYPE_HPP__
#define __MSTK_INCLUDE_MSTK_FILTERTYPE_HPP__

#include <boost/shared_ptr.hpp>

#include <mstk/config.hpp>
#include <mstk/Filter.hpp>

namespace mstk {

template <class A, class M> 
class FilterType : public Filter
{
  public:
    // constructors, etc
    FilterType();
    virtual ~FilterType();
    // get and set
    boost::shared_ptr<A> getAlgorithm();
    boost::shared_ptr<M> getManager();
  protected:
    boost::shared_ptr<A> algorithm_;
    boost::shared_ptr<M> manager_;
};

} // namespace mstk

//
// implementation
//

namespace mstk {

template <class A, class M>
FilterType<A, M>::FilterType() 
  : Filter(), algorithm_(new A), manager_(new M)
{
}

template <class A, class M>
FilterType<A, M>::~FilterType()
{
}

template <class A, class M>
boost::shared_ptr<A> FilterType<A, M>::getAlgorithm()
{
    return algorithm_;
}

template <class A, class M>
boost::shared_ptr<M> FilterType<A, M>::getManager()
{
    return manager_;
}

} // namespace mstk

#endif

