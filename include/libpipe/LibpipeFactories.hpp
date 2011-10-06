/*
 * libpipeFactories.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPEFACTORIES_HPP_
#define LIBPIPEFACTORIES_HPP_

#include "libpipe/utilities/Singleton.hpp"
#include "libpipe/utilities/Factory.hpp"
#include "libpipe/Algorithm.hpp"
#include "libpipe/Manager.hpp"
#include "libpipe/BasicFilterRTC.hpp"

namespace libpipe {
namespace RTC {

typedef utilities::Singleton<
        utilities::Factory<libpipe::Algorithm, std::string> > AlgorithmFactory;

typedef utilities::Singleton<
        utilities::Factory<libpipe::Manager, std::string> > ManagerFactory;

typedef utilities::Singleton<
        utilities::Factory<libpipe::RTC::BasicFilter, std::string> > FilterFactory;

} //end namespace RTC
} //end namespace libpipe
#endif /* LIBPIPEFACTORIES_HPP_ */
