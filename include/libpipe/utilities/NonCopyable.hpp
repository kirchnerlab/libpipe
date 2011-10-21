/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2011 Marc Kirchner
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
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_NONCOPYABLE_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_NONCOPYABLE_HPP__

namespace libpipe {
namespace utilities {

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
    NonCopyable()
    {
    }
    ~NonCopyable()
    {
    } // *not* virtual
private:
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator=(const NonCopyable&);
};

} // end namespace utilities
} // end namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_NONCOPYABLE_HPP__

