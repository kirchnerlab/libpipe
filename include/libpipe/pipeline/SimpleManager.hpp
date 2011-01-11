/*
 * SimpleManager.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_SIMPLEMANAGER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_SIMPLEMANAGER_HPP__

#include <libpipe/config.hpp>
#include <set>
#include <libpipe/pipeline/Manager.hpp>
#include <libpipe/pipeline/Request.hpp>
#include <libpipe/pipeline/RequestException.hpp>

namespace libpipe {

// forward declarations
class Algorithm;
class Filter;

/** Provides simple pipeline management.
 */
class SimpleManager : public Manager
{
  public:
    SimpleManager();
    virtual ~SimpleManager();

    void setAlgorithm(libpipe::Algorithm* alg);
    virtual libpipe::Request& processRequest(libpipe::Request& req);
    void connect(Filter* sm);

  protected:
    typedef std::set<Filter*> ManagerSet;
    ManagerSet sources_;
    libpipe::Algorithm* algorithm_;
};

} // namespace libpipe

#endif

