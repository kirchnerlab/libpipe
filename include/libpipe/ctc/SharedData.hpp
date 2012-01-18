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
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_CTC_SHAREDDATA_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_CTC_SHAREDDATA_HPP__

#include <libpipe/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <memory>

namespace libpipe {
namespace ctc {

/** A template class used to hold data that is shared between algorithms.
 * Sometimes algorithm objects are not able to immediately instantiate a result
 * object but need to process data beforehand. The two foremost cases where
 * this holds true are: (1) using external classes that implement the 'object
 * initialization is resource allocation' idiom, where the allocation depends
 * on user parameters; (2) using external classes whose final type is data
 * dependent (e.g the well-known Shape/Rectangle/Circle example). In both
 * cases, the final object does not exist while the filters and algorithms are
 * connected. As a consequence, in- and out-data between algorithms cannot be
 * connected either: there is no point in issuing
 * alg1->setInput(alg0->getOutput()), if alg0->getOutput() still is a null
 * pointer.
 *
 * \c SharedData overcomes this problem by essentially providing a proxy object
 * that always allows to default-construct the shared data and to write the 
 * following code:
 * 
 * \li in Alg0.hpp
 * 
 * \code
 * ...
 * public:
 * ...
 * boost::shared_ptr<SharedData<MyType> > getOutput();
 * ...
 * private:
 * ...
 * boost::shared_ptr<SharedData<MyType> > output_;
 * ...
 * \endcode
 *
 * \li in Alg0.cpp
 * 
 * \code
 * ...
 * Alg0::Alg0() : output_(boost::make_shared<SharedData<MyType> >())
 * ...
 * \endcode
 *
 * \li in Alg1.hpp
 *
 * \code
 * ...
 * void setInput(boost::shared_ptr<SharedData<MyType> > p);
 * ...
 * \endcode
 *
 * \li in Alg1.cpp
 *
 * \code
 * ...
 * Request& processRequest(Request& req)
 * {
 *     ...
 *     if (!input_.isNull()) {
 *         ... run the algorithm ...
 *     } else {
 *         ... report the error condition into the request object
 *         ... or throw an exception.
 *     }
 *     ...
 *     return req;
 * }
 * \endcode
 *
 * \li somewhere in main.cpp
 * 
 * \code
 * ...
 * filter1->getAlgorithm()->setInput(filter0->getAlgorithm()->getOutput())
 * \endcode
 *
 * Note that this simply guarantees that two connected algorithms will always
 * be able to share data, irrespective of the question if the source side is
 * capable of providing the data structure immediately upon construction or
 * not.
 * @ingroup ctc
 */
template<typename T>
class LIBPIPE_EXPORT SharedData : boost::noncopyable
{
public:
    /** Constructor.
     */
    SharedData();

    /** Construct from an existing pointer, taking over ownership.
     * The best practice follows the \c auto_ptr and \c shared_ptr idioms:
     * call new in the parameters.
     * \code
     * ...
     * SharedData<int> x(new int);
     * ...
     * x.set(new int);
     * *(x.get()) = 10;
     * ...
     * \endcode
     *
     * @param[in] ptr Pointer to a \c T instance or 0. If \c ptr is a valid
     *                pointer, \c SharedData takes ownership!
     */
    SharedData(T* ptr);

    /** Desctructor.
     */
    ~SharedData();

    /** Returns a pointer to the wrapped object.
     * There are no constness constraints on the object.
     * @return A pointer to the wrapped object.
     */
    T* get() const;

    /** Set the shared object.
     * @see SharedData<T>::SharedData(T* ptr)
     * @param[in] ptr Pointer to the shared object, ownership is taken over!
     */
    void set(T* ptr);

    /** Convenience function to check if the \c SharedData holds a valid
     * object.
     * @return True if the \c SharedData object points to a valid \c T
     *         instance.
     */
    bool isNull();

private:
    /** Pointer to the \c T instance.
     */
    boost::scoped_ptr<T> ptr_;
};

//
// template implementations
//
template<typename T>
SharedData<T>::SharedData() :
ptr_(0)
{
}

template<typename T>
SharedData<T>::SharedData(T* ptr) :
ptr_(ptr)
{
}

template<typename T>
SharedData<T>::~SharedData()
{
}

template<typename T>
T* SharedData<T>::get() const
{
    return ptr_.get();
}

template<typename T>
void SharedData<T>::set(T* ptr)
{
    if (ptr != ptr_.get()) {
        ptr_.reset(ptr);
    }
}

template<typename T>
bool SharedData<T>::isNull()
{
    return ptr_.get() == 0;
}

} // end namespace ctc
} // end namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_CTC_SHAREDDATA_HPP__
