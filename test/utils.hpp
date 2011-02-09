/*
 * utils.hpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 * Helper classes for test case development.
 *
 */
#ifndef __LIBPIPE_TEST_UTILS_HPP__
#define __LIBPIPE_TEST_UTILS_HPP__

#include <libpipe/Algorithm.hpp>
#include <libpipe/BasicFilter.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/Manager.hpp>

#include <sstream>

using namespace libpipe;

/** An algorithm that does not change its input.
 */
class Identity : public Algorithm
{
  public:
    Identity() : Algorithm(), in_(0), out_(0) {}
    ~Identity() {}
    Request& update(Request& req) {
        LIBPIPE_REQUEST_TRACE(req, "Identity: copying value.");
        out_ = in_;
        this->updateMTime();
        return req;
    }
    int getOutput() { return out_; }
    void setInput(int input) {
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
    Inc() : Algorithm(), out_(new int(0)) {}
    ~Inc() { delete out_; }
    Request& update(Request& req) {
        std::ostringstream oss;
        *out_ = (*in_)+1;
        oss << "Inc: " << *in_ << " -> " << *out_;
        LIBPIPE_REQUEST_TRACE(req, oss.str());
        this->updateMTime();
        return req;
    }
    int* getOutput() { return out_; }
    void setInput(int* input) {
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
    RaiseExceptionAlg() : Algorithm() {}
    ~RaiseExceptionAlg() {}
    Request& update(Request& req) {
        // deliberately raise a non-libpipe exception
        throw std::exception();
    }
};

/** Derive from Manager to be able to access the protected classes
 * for testing.
 */
class TestManager : public Manager {
  public:
    std::set<Filter*> getSources() { return sources_; }
};

#endif
