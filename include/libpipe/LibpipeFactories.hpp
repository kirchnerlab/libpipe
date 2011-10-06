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



namespace libpipe_rtc {

class FilterRTC;
class AlgorithmRTC;
class ManagerRTC;

typedef utilities::Singleton<
        utilities::Factory<AlgorithmRTC, std::string> > AlgorithmFactory;

typedef utilities::Singleton<utilities::Factory<ManagerRTC, std::string> > ManagerFactory;

typedef utilities::Singleton<
            utilities::Factory<
                FilterRTC,
                std::string,
                utilities::ErrorPolicyThrowException,
                FilterRTC* (*)(const std::string&, const std::string&, const std::string&)> > FilterFactory;

} //end namespace libpipe_rtc
#endif /* LIBPIPEFACTORIES_HPP_ */
