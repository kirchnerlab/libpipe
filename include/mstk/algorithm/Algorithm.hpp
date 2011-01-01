/*
 * Algorithm.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_ALGORITHM_HPP__
#define __MSTK_INCLUDE_MSTK_ALGORITHM_HPP__

#include <mstk/config.hpp>

#include <string>
#include <map>
#include <mstk/pipeline/Request.hpp>

namespace mstk {


/** Base class for all MSTK algorithms.
 */
class Algorithm
{
  public:
    /** Pure virtual descructor.
     */
    virtual ~Algorithm() = 0;
    
    /** Processes the current request object.
     * Depending on the information contained in the request object,  this will
     * call the \c update function 
     */
    virtual Request& processRequest(Request& req);

    /** Runs the algorithm and updates the output data.
     * Users must overload this method (this is where the beef goes).
     * @param[in,out] req The request object (useful for logging/tracing
     *                   purposes.
     */
    virtual Request& update(Request& req) = 0;
};

} // namespace mstk

#endif

