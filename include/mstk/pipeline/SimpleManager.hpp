/*
 * SimpleManager.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_SIMPLEMANAGER_HPP__
#define __MSTK_INCLUDE_MSTK_SIMPLEMANAGER_HPP__

#include <mstk/config.hpp>
#include <set>
#include <mstk/pipeline/Manager.hpp>
#include <mstk/pipeline/Request.hpp>
#include <mstk/pipeline/RequestException.hpp>

namespace mstk {

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

    void setAlgorithm(mstk::Algorithm* alg);
    virtual mstk::Request& processRequest(mstk::Request& req);
    void connect(Filter* sm);

  protected:
    typedef std::set<Filter*> ManagerSet;
    ManagerSet sources_;
    mstk::Algorithm* algorithm_;
};

} // namespace mstk

#endif

