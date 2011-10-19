/*
 * AlgorithmFactory.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_ALGORITHMFACTORY_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_ALGORITHMFACTORY_HPP__

#include "libpipe/utilities/Singleton.hpp"
#include "libpipe/utilities/Factory.hpp"

namespace libpipe {
namespace rtc {

class Algorithm;

/** The Algorithm Factory
 */
typedef utilities::Singleton<utilities::Factory<Algorithm, std::string> > AlgorithmFactory;

} // namespace rtc
} // namespace libpipe

#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_ALGORITHMFACTORY_HPP__ */
