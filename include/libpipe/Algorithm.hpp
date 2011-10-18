/*
 * Algorithm.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_ALGORITHM_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_ALGORITHM_HPP__

#include <libpipe/config.hpp>

#include <string>
#include <libpipe/Request.hpp>
#include <sys/time.h> // for timeval
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

namespace libpipe {

/** Base class for all LIBPIPE algorithms.
 */
class Algorithm
{
public:
    /** Holds the maximum time value that can be represented in a
     * timeval struct.
     * This is mostly necessary for initialization, but also for the correct
     * behaviour of filters that act as sources.
     * @see updateMTime(), needUpdate()
     */
    static const timeval MAX_TIME;

    /** Holds the minimum time value that can be represented in a
     * timeval struct.
     * This is mostly necessary for disconnecting the input filter.
     */
    static const timeval MIN_TIME;

    /** Constructor.
     */
    Algorithm();

    /** Pure virtual descructor.
     */
    virtual ~Algorithm() = 0;

    /** Processes the current request object.
     * Depending on the information contained in the request object,  this will
     * call the \c update function 
     * @param [in,out] req A request object.
     * @return A (potentially modified) request object.
     */
    virtual Request& processRequest(Request& req);

    /** Runs the algorithm and updates the output data, if the Request
     * Type is \c Request::Update. If the request Type is \c Request::DELETE
     * after calling the update function the modification time is fixed to
     * \c Algorithm::MIN_TIME.
     * Users must overload this method (this is where the beef goes).
     * @param [in,out] req The request object (useful for logging/tracing
     *                   purposes). Also useful to get the type of request
     *                   (Update of Delete), so that the input can be deleted.
     * @return Request object
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
     * \li When the precursors are deleted the modification time gets set to
     *     \c Algorithm::MIN_TIME to guarantee that the algorithm does not
     *     update himself.
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
    /** Initializes the static constant \c MAX_TIME.
     * @return The maximum valid entry in a timeval struct.
     */
    static timeval initMaxTime();

    /** Initializes the static constant \c MIN_TIME.
     * @return The minimum valid entry in a timeval struct.
     */
    static timeval initMinTime();

    /** The last modification timestamp.
     */
    timeval mTime_;
};

} // namespace libpipe

#endif

