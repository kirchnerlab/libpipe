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

#include <libpipe/algorithm/Algorithm.hpp>
#include <libpipe/pipeline/BasicFilter.hpp>
#include <libpipe/pipeline/Request.hpp>
#include <libpipe/pipeline/RequestException.hpp>
#include <libpipe/pipeline/Manager.hpp>

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
