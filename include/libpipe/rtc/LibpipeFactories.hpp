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




namespace libpipe {
namespace rtc {

class Algorithm;
class Manager;

typedef utilities::Singleton<
        utilities::Factory<Algorithm, std::string> > AlgorithmFactory;

typedef utilities::Singleton<utilities::Factory<Manager, std::string> > ManagerFactory;

} // namespace rtc
} // namespace libpipe
#endif /* LIBPIPEFACTORIES_HPP_ */
