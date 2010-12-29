/*
 * Algorithm.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_ALGORITHM_HPP__
#define __MSTK_INCLUDE_MSTK_ALGORITHM_HPP__

#include <mstk/config.hpp>

#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

#include <mstk/PortInformation.hpp>

namespace mstk {


/** Base class for all MSTK algorithms.
 */
class Algorithm
{
  public:
    // convenience typedef
    typedef std::map<std::string, PortInformation> PortInformationMap;

    /** Pure virtual descructor.
     */
    virtual ~Algorithm() = 0;
    
    /** Processes the current request.
     * Derived classes should run the algorithm upon this method being called.
     */
    virtual void processRequest() = 0;

    /** Return information on all input ports.
     */
    virtual PortInformationMap getInputPortInformation() const;

    /** Return information on all output ports.
     */
    virtual PortInformationMap getOutputPortInformation() const;

  protected:
    /** Add input port information.
     * @param[in] pInfo The information describing an input port.
     */
    virtual void addInputPortInformation(const PortInformation& pInfo);

    /** Add output port information.
     * @param[in] pInfo The information describing an output port.
     */
    virtual void addOutputPortInformation(const PortInformation& pInfo);

    /** The information on all output ports, indexed by their name.
     */
    PortInformationMap outputPortInformation_;

    /** The information on all input ports, indexed by their name.
     */
    PortInformationMap inputPortInformation_;
};

} // namespace mstk

#endif

