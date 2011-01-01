/*
 * BasicFilter.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_BASICFILTER_HPP__
#define __MSTK_INCLUDE_MSTK_BASICFILTER_HPP__

#include <mstk/config.hpp>
#include <string>
#include <mstk/pipeline/Filter.hpp>

namespace mstk {

/** Wraps an algorithm and a manager into a Filter.
 * This is the preferred way of creating a filter type from given \c Algorithm
 * and Manager types. Assuming the user has implemented an algorithm in a class
 * \c UserAlgorithm and makes use of the \c SimpleManager, the corresponding
 * filter is acquired using
 * \code
 * #include <mstk/SimpleManager.hpp>
 * ...
 * using namespace mstk;
 * ...
 * typedef BasicFilter<UserAlgorithm, SimpleManager> UserFilter;
 * ...
 * \endcode
 * The filter can then be used in the usual way:
 * \code
 * ...
 * UserFilter* uf = new UserFilter("FilterName");
 * uf->getAlgorithm()->setParameters(...);
 * ...
 * uf->getManager()->connect(someOtherFilter->getManager());
 * uf->getAlgorithm()->setInputFoo(someOtherFilter->getAlgorithm()->getOutputBar());
 * ...
 * \endcode
 */
template <class A, class M>
class BasicFilter : public mstk::Filter
{
  public:

    /** Constructor.
     * @param name The name of the filter. Passed through to mstk::Filter.
     */
    BasicFilter(const std::string& name);

    /** Destructor.
     * Virtual, to allow for subclassing.
     */
    virtual ~BasicFilter();

    /** Provides access to the algorithm object.
     * This is a small hack: we need to redefine \c getAlgorithm in each Filter
     * because there is only a minimal fixed interface for \c Algorithm, that
     * does not include all potential functions a user might add.
     * @return A pointer (with the true class type) to the algorithm object.
     */
    A* getAlgorithm();
    
    /** Provides access to the manager object.
     * @see getAlgorithm.
     * @return A pointer (with the true class type) to the manager object.
     */
    M* getManager();
};

/*
 * Template implementation
 */
template <class A, class M>
BasicFilter<A, M>::BasicFilter(const std::string& name) 
  : mstk::Filter(name) 
{
    this->setAlgorithm(new A);
    M* sm = new M;
    sm->setAlgorithm(this->getAlgorithm());
    this->setManager(sm);
}

template <class A, class M>
BasicFilter<A, M>::~BasicFilter()
{}

template <class A, class M>
A* BasicFilter<A, M>::getAlgorithm() {
    return dynamic_cast<A*>(this->algorithm_);
}

template <class A, class M>
M* BasicFilter<A, M>::getManager() {
    return dynamic_cast<M*>(this->manager_);
}

} // namespace mstk

#endif

