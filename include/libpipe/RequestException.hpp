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
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_REQUESTEXCEPTION_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_REQUESTEXCEPTION_HPP__

#include <libpipe/config.hpp>

#include <libpipe/utilities/Exception.hpp>

namespace libpipe {
/** Class for Request Exceptions
 */
class LIBPIPE_EXPORT RequestException : public utilities::Exception
{
public:
    /** Constructor.
     * @param msg The error message.
     */
    RequestException(const char* msg) :
        Exception(msg)
    {
    }

    /** Constructor.
     * @param msg The error message.
     */
    RequestException(const std::string& msg) :
        Exception(msg)
    {
    }

    /** Destructor.
     */
    virtual ~RequestException() throw ()
    {
    }
};

}

#endif //__LIBPIPE_INCLUDE_LIBPIPE_REQUESTEXCEPTION_HPP__

