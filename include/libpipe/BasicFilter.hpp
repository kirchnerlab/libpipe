/*
 * BasicFilter.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_BASICFILTER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_BASICFILTER_HPP__

#include <libpipe/config.hpp>
#include <string>
#include <libpipe/Filter.hpp>

namespace libpipe {

/** Wraps an algorithm and a manager into a Filter.
 * This is the preferred way of creating a filter type from given \c Algorithm
 * and Manager types. Assuming the user has implemented an algorithm in a class
 * \c UserAlgorithm and makes use of the \c normal Manager, the corresponding
 * filter is acquired using
 * \code
 * #include <libpipe/Manager.hpp>
 * ...
 * using namespace libpipe;
 * ...
 * typedef BasicFilter<UserAlgorithm, Manager> UserFilter;
 * ...
 * \endcode
 * The filter can then be used in the usual way:
 * \code
 * ...
 * boost::shared_ptr<UserFilter> uf (new UserFilter("FilterName"));
 * uf->getAlgorithm()->setParameters(...);
 * ...
 * uf->getManager()->connect(boost::dynamic_pointer_cast<Filter>(someOtherFilter->getManager()));
 * uf->getAlgorithm()->setInputFoo(someOtherFilter->getAlgorithm()->getOutputBar());
 * ...
 * \endcode
 */
template<class A, class M>
class BasicFilter : public Filter
{
public:

    /** Constructor.
     * @param name The name of the filter. Passed through to libpipe::Filter.
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
    virtual A* getAlgorithm();

    /** Provides access to the manager object.
     * @see getAlgorithm.
     * @return A pointer (with the true class type) to the manager object.
     */
    virtual M* getManager();
};

/*
 * Template implementation
 */
template<class A, class M>
BasicFilter<A, M>::BasicFilter(const std::string& name) :
    Filter(name)
{
    A* a = new A;
    M* m = new M;
    this->setManager(m);
    this->setAlgorithm(a);
}

template<class A, class M>
BasicFilter<A, M>::~BasicFilter()
{
}

template<class A, class M>
A* BasicFilter<A, M>::getAlgorithm()
{
    return dynamic_cast<A*> (Filter::getAlgorithm());
}

template<class A, class M>
M* BasicFilter<A, M>::getManager()
{
    return dynamic_cast<M*> (Filter::getManager());
}

} // namespace libpipe

#endif

