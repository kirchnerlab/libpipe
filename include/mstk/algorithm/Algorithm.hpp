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
#include <ostream>

/** Comparison operator for \c struct \c timeval objects.
 */
bool operator==(const timeval& lhs, const timeval& rhs);

/** Comparison operator for \c struct \c timeval objects.
 */
bool operator<=(const timeval& lhs, const timeval& rhs);

/** Stream operator for timeval structs.
 */
std::ostream& operator<<(std::ostream& os, const timeval& tv);

namespace mstk {

/** Base class for all MSTK algorithms.
 */
class Algorithm
{
  public:
    
    static timeval initMaxTime();
    static timeval MAX_TIME;

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

    
    /** Returns a flag that signifies if the Algorithm needs an update,
     * irrespective of its modification time.
     * The function essentially tests it the modification time of the algorithm
     * is equal to \c Algorithm::MAX_TIME, signifying that the algorithm needs
     * to be run and that its modification time value should be disregarded.
     * Managers must check \c needUpdate prior to making use of the information
     * delivered by \c getMTime.
     * There are two major application scenarios that make use of the flag:
     * \li When algorithms are instantiated for the first time, their creation
     *     date need not coincide with the execution sequence (this is
     *     especially true for filter setups with branches). Hence, their
     *     modification time is set to \c Algorithm::MAX_TIME to guarantee
     *     their execution on the first call to \c update.
     * \li Managers in filters that act as sources (i.e. do not have any
     *     predecessor) cannot determine the need for execution by comparing \c
     *     Algorithm::getMTime() against their predecessor. In the event that
     *     their internal state changes, the manager needs to call \c
     *     this->getAlgorithm()->setMTime(Algorithm::MAX_TIME), thus enforcing
     *     an update of the source and propagation along the filter chain.
     * @return Boolean flag that indicates the need for a call to the
     *         algorithm's \c update function.
     */
    bool needUpdate() const;

  private:
    /** The last modification timestamp.
     */
    timeval mTime_;
};

} // namespace mstk

#endif

