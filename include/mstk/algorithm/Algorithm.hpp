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
#include <ctime>

/** Comparison operator for \c struct \c timeval objects.
 */
bool operator<(const timeval& lhs, const timeval& rhs);

namespace mstk {

/** Base class for all MSTK algorithms.
 */
class Algorithm
{
  public:
    /** Constructor.
     */
    Algorithm();

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

    /** Return the last modification timestamp.
     * @return The last modification timestamp.
     */
    const timeval& getMTime() const;

    /** Set the last modification timestamp.
     * @param[in] tv Timestamp.
     */
    void setMTime(const timeval& tv);

    /** Update the modification timestamp to the current system time.
     */
    void updateMTime();

  private:
    /** The last modification timestamp.
     */
    timeval mTime_;
};

} // namespace mstk

#endif

