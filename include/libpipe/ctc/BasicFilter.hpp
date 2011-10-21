/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2010 Marc Kirchner
*
* This file is part of libpipe.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_CTC_BASICFILTER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_CTC_BASICFILTER_HPP__

#include <libpipe/config.hpp>
#include <string>
#include <libpipe/ctc/Filter.hpp>

namespace libpipe {

namespace ctc {

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

} // end namspace ctc
} // end namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_CTC_BASICFILTER_HPP__

