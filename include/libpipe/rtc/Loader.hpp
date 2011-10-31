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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__

#include <libpipe/config.hpp>

#include <libpipe/rtc/Pipeline.hpp>
#include <string>
#include <map>

namespace libpipe {
namespace rtc {


class Loader
{
    public:
        /** Constructor
         * @param filename Name of the input files. With a key.
         */
        Loader(const std::map<std::string, std::string>& filename);
        /**
         * Destructor
         */
        ~Loader();

        /**
         * Returns the pipeline object
         * @return A pipeline Object
         */
        Pipeline getPipeline() const;

    private:
        /**
         * The pipeline Object
         */
        Pipeline pipeline_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_LOADER_HPP__ */
