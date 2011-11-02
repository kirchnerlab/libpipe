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

#include <libpipe/config.hpp>

#include <libpipe/rtc/Loader.hpp>
#include <libpipe/rtc/Controler.hpp>
#include <libpipe/utilities/Exception.hpp>

#include <string>
#include <fstream>

namespace libpipe {
namespace rtc {

Loader::Loader(const std::map<std::string, std::string>& filename)
{

    Controler creator_(filename);
    pipeline_ = creator_.getPipeline();

}

Loader::~Loader()
{
}

Pipeline Loader::getPipeline() const
{
    return pipeline_;
}

} /* namespace rtc */
} /* namespace libpipe */
