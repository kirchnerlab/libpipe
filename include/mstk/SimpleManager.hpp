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
#include <mstk/Algorithm.hpp>
#include <mstk/Manager.hpp>
#include <mstk/Request.hpp>

namespace mstk {

class SimpleManager : public Manager
{
  public:
    SimpleManager();
    ~SimpleManager();

    void setAlgorithm(mstk::Algorithm* alg);
    mstk::Request& processRequest(mstk::Request& req);
    void connect(SimpleManager* sm);

  protected:
    typedef std::set<Manager*> ManagerSet;
    ManagerSet sources_;
    mstk::Algorithm* algorithm_;
};

} // namespace mstk

#endif

