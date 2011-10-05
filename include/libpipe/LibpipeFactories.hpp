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

namespace RTC {

typedef utilities::Singleton<
        libpipe::utilities::ObjectFactory<libpipe::Algorithm, std::string> > AlgorithmFactory;

typedef utilities::Singleton<
        libpipe::utilities::ObjectFactory<libpipe::Manager, std::string> > ManagerFactory;

//TODO add Factory for Basicfilter when implemented
//typedef Singleton<
//        libpipe::FactorySite::ObjectFactory<libpipe::FIXME, std::string> > FilterFactory;

} //end namespace RTC
#endif /* LIBPIPEFACTORIES_HPP_ */
