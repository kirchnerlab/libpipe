/*
 * NonCopyable.hpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_NONCOPYABLE_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_NONCOPYABLE_HPP__

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
    NonCopyable() {}
    ~NonCopyable() {} // *not* virtual
  private:
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator=(const NonCopyable&);
};

} // namespace libpipe

#endif

