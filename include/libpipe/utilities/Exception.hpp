/*
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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_EXCEPTION_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_EXCEPTION_HPP__

#include <libpipe/config.hpp>
#include <boost/exception/all.hpp>
#include <string>

namespace libpipe {
namespace utilities {

/** libpipe expection base class.
 */
class LIBPIPE_EXPORT Exception : public boost::exception
{
public:
    /** Constructor for C-style string error messages.
     *  @param message C-style string error message.
     *                 The string contents are copied upon construction
     *                 Responsibility for deleting the \c char* lies
     *                 with the caller. 
     */
    explicit Exception(const char* message);

    /** Constructor for STL string class error messages.
     *  @param message The error message.
     */
    explicit Exception(const std::string& message);

    /** Destructor. Nothrow guarantee.
     * Virtual to allow for subclassing.
     */
    virtual ~Exception() throw ();

    /** Returns a pointer to the constant error message.
     *  @return A pointer to a \c const \c char*. The underlying memory
     *          is in posession of the \c Exception object. Callers \a must
     *          not attempt to free the memory.
     */
    virtual const char* what() const throw ();

protected:
    /** Error message.
     */
    std::string msg_;
};

/** Convenience macros.
 */
#define libpipe_fail(ERROR_MESSAGE) throw boost::enable_current_exception(libpipe::utilities::Exception(ERROR_MESSAGE))

} // end namespace utilities
} // end namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_EXCEPTION_HPP__
