/*
 *
 * Copyright (c) 2011 David-Matthias Sichau
 * Copyright (c) 2010 Marc Kirchner
 *
 * This file is part of libpipe.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_CTC_ALGORITHM_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_CTC_ALGORITHM_HPP__

#include <libpipe/config.hpp>

#include <string>
#include <map>
#include <libpipe/Request.hpp>
#include <ostream>
#include <libpipe/utilities/Time.hpp> // for timeval

namespace libpipe {
/**
 * @namespace libpipe::ctc \c libpipe compile time configuration.
 */
namespace ctc {

/**
 *  @defgroup ctc Code related to the compile-time configuration
 *                of \c libpipe.
 */

/** Base class for all \c libpipe algorithms that support runtime configuration.
* @ingroup ctc
*/
class LIBPIPE_EXPORT Algorithm
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
     * @param[in,out] req A request object.
     */
    void processRequest(Request& req);

    /** Runs the algorithm and updates the output data, if the Request
     * Type is \c Request::Update. If the request Type is \c Request::DELETE
     * after calling the update function the modification time is fixed to
     * \c Algorithm::MIN_TIME.
     * Users must overload this method (this is where the beef goes).
     * @param[in,out] req The request object (useful for logging/tracing
     *                   purposes). Also useful to get the type of request
     *                   (Update of Delete), so that the input can be deleted.
     */
    virtual void update(Request& req) = 0;

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

} // end namespace ctc
} // namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_CTC_ALGORITHM_HPP__
