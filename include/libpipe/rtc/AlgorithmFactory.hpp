/*
 * AlgorithmFactory.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef ALGORITHMFACTORY_HPP_
#define ALGORITHMFACTORY_HPP_

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

#endif /* ALGORITHMFACTORY_HPP_ */
