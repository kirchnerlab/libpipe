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


namespace libpipe_rtc {

class BasicFilterRTC;


typedef utilities::Singleton<
        utilities::Factory<libpipe::Algorithm, std::string> > AlgorithmFactory;

typedef utilities::Singleton<utilities::Factory<libpipe::Manager, std::string> > ManagerFactory;

typedef utilities::Singleton<
            utilities::Factory<
                BasicFilterRTC,
                std::string,
                utilities::ErrorPolicyThrowException,
                BasicFilterRTC* (*)(const std::string&, const std::string&, const std::string&)> > FilterFactory;

} //end namespace libpipe_rtc
#endif /* LIBPIPEFACTORIES_HPP_ */
