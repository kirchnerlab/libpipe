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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_SHAREDDATA_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_SHAREDDATA_HPP__

#include <libpipe/config.hpp>

#include <libpipe/rtc/Data.hpp>
#include <libpipe/utilities/Exception.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <memory>
#ifdef ENABLE_THREADING
#include <boost/thread.hpp>
#endif

namespace libpipe {

namespace rtc {

/** Macro that prepares the stored data for read access in update methods
 * This is just for convenience.
 * @param varName the variable name where the input is stored
 * @param dataReference the reference to the data stored in varName
 * @param type Type of the data returned by dataReference
 * @param portName String of the corresponding port name
 * @attention Do not forget to unlock varName at the end of the update method if you have multithreading enabled!
 */
#ifdef ENABLE_THREADING
#define LIBPIPE_PREPARE_READ_ACCESS(varName, dataReference, type, portName)   \
        boost::shared_ptr<libpipe::rtc::SharedData<type> > varName = boost::dynamic_pointer_cast<libpipe::rtc::SharedData<type> >(this->getPort(portName)); \
        varName->shared_lock(); \
        const type& dataReference = *(varName->get());
#else
#define LIBPIPE_PREPARE_READ_ACCESS(varName, dataReference, type, portName)   \
        boost::shared_ptr<libpipe::rtc::SharedData<type> > varName = boost::dynamic_pointer_cast<libpipe::rtc::SharedData<type> >(this->getPort(portName)); \
        const type& dataReference = *(varName->get());
#endif

/** Macro that prepares the stored data for write access in update methods
 * This is just for convenience.
 * @param varName the variable name where the input is stored
 * @param dataReference the reference to the data stored in varName
 * @param type Type of the data returned by dataReference
 * @param portName String of the corresponding port name
 * @attention Do not forget to unlock varName at the end of the update method if you have multithreading enabled!
 *
 */
#ifdef ENABLE_THREADING
#define LIBPIPE_PREPARE_WRITE_ACCESS(varName, dataReference, type, portName)   \
        boost::shared_ptr<libpipe::rtc::SharedData<type> > varName = boost::dynamic_pointer_cast<libpipe::rtc::SharedData<type> >(this->getPort(portName)); \
        varName->lock(); \
        type& dataReference = *(varName->get());
#else
#define LIBPIPE_PREPARE_WRITE_ACCESS(varName, dataReference, type, portName)   \
        boost::shared_ptr<libpipe::rtc::SharedData<type> > varName = boost::dynamic_pointer_cast<libpipe::rtc::SharedData<type> >(this->getPort(portName)); \
        type& dataReference = *(varName->get());
#endif

/** A template class used to hold data that is shared between algorithms.
 * Sometimes algorithm objects are not able to immediately instanciate a result
 * object but need to process data beforehand. The two foremost cases where
 * this holds true are: (1) using external classes that implement the 'object
 * initialization is resource allocation' idiom, where the allocation depends
 * on user parameters; (2) using external classes whose final type is data
 * dependent (e.g the well-known Shape/Rectangle/Circle example). In both
 * cases, the final object does not exist while the filters and algorithms are
 * connected.
 * Note that this simply guarantees that two connected algorithms will always
 * be able to share data, irrespective of the question if the source side is
 * capable of providing the data structure immediately upon construction or
 * not.
 * This class also has a fast implementation for safe multithreading.
 * @ingroup rtc
 */
template<typename T>
class LIBPIPE_EXPORT SharedData : boost::noncopyable, public Data
{
public:
    /** Constructor.
     */
    SharedData();

    /** Construct from an existing pointer, taking over ownership.
     * Best practice corresponds to the \c auto_ptr and \c shared_ptr best
     * practices, see
     * http://www.boost.org/doc/libs/1_48_0/libs/smart_ptr/shared_ptr.htm
     * In particular, always use a named SharedData object to hold the
     * result of new:
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
     *                pointer, \c SharedData takes ownership.
     */
    SharedData(T* ptr);

    /** Desctructor.
     */
    ~SharedData();

#ifdef ENABLE_THREADING
    /** Locks access to the object for single-threaded write access.
     */
    void lock();
    /** Locks access to the object for multi-threaded read access.
     */
    void shared_lock();
    /** Releases a lock held on the object.
     */
    void unlock();

#endif

    /** Returns a pointer to the wrapped object.
     * There are no constness constraints on the object.
     * @return A pointer to the wrapped object.
     */
    T* get() const;

    /** Set the shared object.
     * @see SharedData<T>::SharedData(T* ptr)
     * @param[in] ptr Pointer to the shared object. \c SharedData takes
     *                ownership and clients must not attempt to delete the
     *                referenced memory.
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

#ifdef ENABLE_THREADING
    /** Mutex/semaphore to control access to \c ptr_
     */
    mutable boost::shared_mutex ptrMutex_;

    /** Available lock types.
     */
    enum LockType
    {
        NOT_LOCKED = 0, SHARED_LOCK = 1, UNIQUE_LOCK = 2
    };

    /** The type of locking the object is currently under.
     */
    LockType lockType_;
#endif
};

//
// template implementations
//
template<typename T>
SharedData<T>::SharedData() :
    ptr_(0)
#ifdef ENABLE_THREADING
, lockType_(NOT_LOCKED)
#endif
{
}

template<typename T>
SharedData<T>::SharedData(T* ptr) :
    ptr_(ptr)
#ifdef ENABLE_THREADING
, lockType_(NOT_LOCKED)
#endif
{
}

template<typename T>
SharedData<T>::~SharedData()
{
}

template<typename T>
T* SharedData<T>::get() const
{
#ifdef ENABLE_THREADING
    if (lockType_ == SHARED_LOCK || lockType_ == UNIQUE_LOCK) {
        return ptr_.get();
    } else {
        libpipe_fail("Lock was not set on SharedData::get()");
    }
#else
    return ptr_.get();
#endif
}

template<typename T>
void SharedData<T>::set(T* ptr)
{
#ifdef ENABLE_THREADING
    if (lockType_ == UNIQUE_LOCK) {
        if (ptr != ptr_.get()) {
            ptr_.reset(ptr);
        }
    } else {
        libpipe_fail("Lock was not set on SharedData::set()");
    }
#else
    if (ptr != ptr_.get()) {
        ptr_.reset(ptr);
    }
#endif
}

template<typename T>
bool SharedData<T>::isNull()
{
#ifdef ENABLE_THREADING
    if (lockType_ == SHARED_LOCK || lockType_ == UNIQUE_LOCK) {
        return ptr_.get() == 0;
    } else {
        libpipe_fail("Lock was not set on SharedData::isNull()");
    }
#else
    return ptr_.get() == 0;
#endif
}

#ifdef ENABLE_THREADING
template<typename T>
void SharedData<T>::lock()
{
    boost::unique_lock<boost::shared_mutex> lock(ptrMutex_);
    lockType_ = UNIQUE_LOCK;
}

template<typename T>
void SharedData<T>::shared_lock()
{
    boost::unique_lock<boost::shared_mutex> lock(ptrMutex_);
    lockType_ = SHARED_LOCK;
}

template<typename T>
void SharedData<T>::unlock()
{
    boost::unique_lock<boost::shared_mutex> lock(ptrMutex_);
    lockType_ = NOT_LOCKED;
}

#endif

} //  namespace rtc
} // namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_RTC_SHAREDDATA_HPP__
