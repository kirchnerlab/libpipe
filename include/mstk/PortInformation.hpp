/*
 * PortInformation.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_PORTINFORMATION_HPP__
#define __MSTK_INCLUDE_MSTK_PORTINFORMATION_HPP__

#include <mstk/config.hpp>
#include <string>

namespace mstk {

/** Stores the meta information for algorithm input and output ports.
 */
class PortInformation
{
  public:
    /** Functor to determine if two PortInformation objects are compatible.
     */
    struct is_compatible : public std::binary_function<
      PortInformation, PortInformation, bool>
    {
         /* Comparison function. 
         * @param[in] outPortInfo Port information of the outgoing port.
         * @param[in] inPortInfo Port information of the ingoing port.
         */
        bool operator()(const PortInformation& outPortInfo,
          const PortInformation& inPortInfo);
    };

    /** The type that is used to describe types.
     * We are using a typedef to keep the choice of type (currently
     * a std::string) extensible. 
     */
    typedef std::string Type;
    
    /** Constructor.
     */
    PortInformation();

    /** Destructor.
     * We provide a virtual destructor to allow for subclassing. 
     */
    virtual ~PortInformation();

    
    /** Returns the name of the port.
     */
    std::string getName() const;


    /** Set the name of the port.
     * @param[in] name The name of the port.
     */
    void setName(const std::string& name);

    /** Returns the type of port.
     */
    Type getType() const;
    
    /** Sets the type of a port.
     * @param[in] t The type of the port.
     */
    void setType(const Type&);

  protected:
    std::string name_;
    Type type_;
};

} // namespace mstk

#endif

