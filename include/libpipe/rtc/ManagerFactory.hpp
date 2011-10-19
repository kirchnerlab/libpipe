/*
 * ManagerFactory.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_MANAGERFACTORY_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_MANAGERFACTORY_HPP__

#include <libpipe/config.hpp>

#include <libpipe/utilities/Singleton.hpp>
#include <libpipe/utilities/Factory.hpp>


namespace libpipe {
namespace rtc {

class Manager;

/** The Manager Factory
 */
typedef utilities::Singleton<utilities::Factory<Manager, std::string> > ManagerFactory;



} // namespace rtc
} // namespace libpipe


#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_MANAGERFACTORY_HPP__ */
