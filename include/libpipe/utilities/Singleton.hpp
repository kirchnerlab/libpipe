/*
 *
 * Copyright (c) 2011 David-Matthias Sichau
 * Copyright (c) 2010 Marc Kirchner
 * Copyright (c) 2008 Thorben Kroeger
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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_SINGLETON_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_SINGLETON_HPP__

#include <libpipe/config.hpp>

#include <exception>
namespace libpipe {
namespace utilities {
/** Singleton holder template class.
 * Template class to create singletons. A singleton instance of class
 * MyType is created and accessed using
 * \code
 * typedef Singleton<MyType> MySingletonType;
 * MyType& myRef = MySingletonType::instance()
 * // ... do something ...
 * \endcode
 */
template<class T>
class LIBPIPE_EXPORT Singleton
{
public:
    /** Return a reference to the only instance of \c Singleton<T>.
     * @return A reference to the instance of the object.
     */
    static T& instance();

    /** Destructor.
     */
    ~Singleton();

private:
    // disallow creation, copying and assignment

    /** Private constructor to disallow explicit construction.
     * Is not defined.
     */
    Singleton();

    /** Private copy constructor to disallow explicit copying.
     * Is not defined.
     * @param S A singleton object.
     */
    Singleton(const Singleton& S);

    /** Provate assignment operator to disallow explicit assignment.
     * Is not defined.
     * @param S A singleton object.
     * @return The current singleton.
     */
    Singleton& operator=(const Singleton& S);

    /** Create method. Creates the singleton instance (a Meyers singleton, ie.
     * a function static object) upon the first call to \c instance().
     */
    static void create();

    /** Pointer to the instance.
     */
    static T* pInstance_;

    /** Status of the singleton. True if the singleton was destroyed.
     */
    static bool destroyed_;

};

/** Returns the unique instance of class T. If it was already
 *  deleted an exception is thrown. If the class T was never used
 *  before a new instance is generated.
 *
 * @return Unique instance of class T
 */
template<class T> T& Singleton<T>::instance()
{
    if (!pInstance_) {
        if (destroyed_) {
            // dead reference
            throw std::exception();
        } else {
            // initial creation
            create();
        }
    }
    return *pInstance_;
}

template<class T> Singleton<T>::~Singleton()
{
    pInstance_ = 0;
    destroyed_ = true;
}

template<class T> void Singleton<T>::create()
{
    static T theInstance;
    pInstance_ = &theInstance;
}

template<class T> T* Singleton<T>::pInstance_ = 0;
template<class T> bool Singleton<T>::destroyed_ = false;

}
}
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_SINGLETON_HPP__ */
