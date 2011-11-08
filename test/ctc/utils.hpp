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
#ifndef __LIBPIPE_TEST_UTILS_HPP__
#define __LIBPIPE_TEST_UTILS_HPP__

#include <libpipe/ctc/Algorithm.hpp>
#include <libpipe/ctc/BasicFilter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/ctc/Manager.hpp>
#include <libpipe/ctc/Pipeline.hpp>

#include <boost/shared_ptr.hpp>

#include <sstream>

using namespace libpipe::ctc;

/** An algorithm that does not change its input.
 */
class Identity : public Algorithm
{
public:
    Identity() :
        Algorithm(), in_(0), out_(0)
    {
    }
    ~Identity()
    {
    }
    libpipe::Request& update(libpipe::Request& req)
    {
        LIBPIPE_PIPELINE_TRACE(req, "Identity: copying value.");
        out_ = in_;
        this->updateMTime();
        return req;
    }
    virtual int getOutput()
    {
        return out_;
    }
    virtual void setInput(int input)
    {
        if (in_ != input) {
            in_ = input;
            this->updateMTime();
        }
    }

private:
    int in_, out_;
};

/** An algorithm that does not change its input.
 * Normally we would use boost::shared_ptr<T> for in- and output, but in order
 * to keep the library and the tests boost-free, we use normal pointers.
 */
class Inc : public Algorithm
{
public:
    Inc() :
        Algorithm(), out_(new int(0))
    {
    }
    ~Inc()
    {
        delete out_;
    }
    libpipe::Request& update(libpipe::Request& req)
    {
        std::ostringstream oss;
        *out_ = (*in_) + 1;
        oss << "Inc: " << *in_ << " -> " << *out_;
        LIBPIPE_PIPELINE_TRACE(req, oss.str());
        this->updateMTime();
        return req;
    }
    int* getOutput()
    {
        return out_;
    }
    void setInput(int* input)
    {
        if (in_ != input) {
            in_ = input;
            this->updateMTime();
        }
    }

private:
    Inc(const Inc&); // don't define
    Inc& operator=(const Inc&); // don't define
    int* in_;
    int* out_;
};

/** An algorithm that throws an exception during execution.
 */
class RaiseExceptionAlg : public Algorithm
{
public:
    RaiseExceptionAlg() :
        Algorithm()
    {
    }
    ~RaiseExceptionAlg()
    {
    }
    libpipe::Request& update(libpipe::Request& req)
    {
        // deliberately raise a non-libpipe exception
        throw std::exception();
    }
};

/** Derive from Manager to be able to access the protected classes
 * for testing.
 */
class TestManager : public Manager
{
public:
    std::set<boost::shared_ptr<Filter> > getSources()
    {
        return sources_;
    }
};

#endif
