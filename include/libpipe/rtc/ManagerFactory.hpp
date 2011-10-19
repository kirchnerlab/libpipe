/*
 * ManagerFactory.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef MANAGERFACTORY_HPP_
#define MANAGERFACTORY_HPP_

#include "libpipe/utilities/Singleton.hpp"
#include "libpipe/utilities/Factory.hpp"


namespace libpipe {
namespace rtc {

class Manager;

/** The Manager Factory
 */
typedef utilities::Singleton<utilities::Factory<Manager, std::string> > ManagerFactory;



} // namespace rtc
} // namespace libpipe


#endif /* MANAGERFACTORY_HPP_ */
