/*
 * NonCopyable.hpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_NONCOPYABLE_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_NONCOPYABLE_HPP__

#include <libpipe/config.hpp>

namespace libpipe {

/** Provides a base class from which classes that would explicitly like to
 * disallow copy construction and assignment can derive. If you derive, use
 * private derivation (there is no point in having a base class pointer of type
 * \c NonCopyable and you normally want to avoid paying the RTTI/vtable price.
 * This is essentially a reimplementation of boost::noncopyable; we don't use
 * the boost class to avoid the dependency.
 */
class NonCopyable
{
    protected:
        /** Constructor
         */
        NonCopyable()
        {
        }
        /** Destructor
         */
        ~NonCopyable()
        {
        } // *not* virtual
    private:
        /** made private to avoid copy Constructor
         * @param t NonCopyable Object
         */
        NonCopyable(const NonCopyable& t);
        /** private asignment operator
         * @param t NonCopyable Object
         * @return NonCopyable Object
         */
        const NonCopyable& operator=(const NonCopyable& t);
};

} // namespace libpipe

#endif

