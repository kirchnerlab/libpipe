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
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_ALGORITHM_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_ALGORITHM_HPP__

#include <libpipe/config.hpp>

#include <libpipe/Request.hpp>
#include <libpipe/rtc/Data.hpp>

#include <map>
#include <libpipe/utilities/Time.hpp> // for timeval
#include <libpipe/utilities/Parameters.hpp>

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#ifdef ENABLE_THREADING
#include <boost/thread.hpp>
#endif

/**
 * \namespace libpipe The \c libpipe default namespace.
 */
namespace libpipe {
/**
 * \namespace libpipe::rtc Namespace for all classes related to the \c libpipe
 *                         runtime configuration functionality.
 */
namespace rtc {

/**
 *  @defgroup rtc Code related to \libpipe runtime configuration.
 */

/** Base class for all \c libpipe algorithms that support runtime configuration.
 * @ingroup rtc
 * This base class establishes the complete interface that is fixed for all
 * algorithms: a pure virtual \c update() function that holds the algorithm
 * implementation, a few helper functions and the data in- and output principle:
 * Filter in- and outputs are controlled through so-called 'ports', each of
 * which has a unique identifier of type \c std::string and points to a
 * \c SharedData<T> instance, where \c T is any class derived from
 * \c rtc::Data.
 */
class LIBPIPE_EXPORT Algorithm
{
public:
    /** Holds the maximum time value that can be represented in a
     * timeval struct.
     * This is necessary for initialization and for the correct
     * behaviour of filters that act as sources.
     * @see updateMTime(), needUpdate()
     */
    static const timeval MAX_TIME;

    /** Holds the minimum time value that can be represented in a
     * timeval struct. This is necessary when disconnecting filter inputs.
     */
    static const timeval MIN_TIME;

    /** create Static constructor. A pointer to this function along with the
     * name of the algorithm is registered with the Algorithm Factory.
     * @return Pointer to a new \c Algorithm instance. Responsibility for
     *         allocated memory lies with the caller.
     */
    static Algorithm* create();

    /** Pure virtual descructor.
     */
    virtual ~Algorithm()=0;

    /** Processes the current request object.
     * In most implementations, this will simply forward the request object
     * to the update function.
     * @param [in,out] req A request object.
     */
    void processRequest(Request& req);

    /** Runs the algorithm and updates the output data, if the Request
     * Type is \c Request::Update. If the request Type is \c Request::DELETE
     * after calling the update function the modification time is fixed to
     * \c Algorithm::MIN_TIME.
     * Users must overload this method (this is where the meat goes).
     * @param [in,out] req The request object, useful to get the type of request
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
     * There are three major application scenarios that make use of the flag:
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

    /** Returns a base class pointer to the data object located at the specified
     * port.
     * @note To actually use the object, it is necessary to caryy out a
     * make dynamic pointer cast to the actual object type, e.g.
     * \code
     * // assuming (*this) is a filter object
     * boost::shared_ptr<Data> port = this->getPort("MyStringInput");
     * typedef libpipe::rtc::SharedData<std::string> SharedString;
     * SharedString sharedStr = boost::dynamic_pointer_cast<SharedString>(port);
     * const std::string& str = *(sharedStr->get())
     * // ...
     * \endcode
     *
     * @param portIdentifier A \c std::string which identifies the port one wants to use
     * @return A shared_ptr to a LibpipeDataObject
     */
    boost::shared_ptr<Data> getPort(const std::string& portIdentifier) const;

    /** Sets the Port to a certain LibpipeDataObject
     * @param portIdentifier A \c std::string which identifies the port one wants to set to
     * the LibpipeDataObject dataObject
     * @param dataObject The Object the Port will point to
     */
    void setPort(const std::string& portIdentifier, boost::shared_ptr<Data> dataObject);

    /** Connects the port of this algorithm identified by thisPortIdentifier to the port of alg algorithm
     * identified by algPortIdentifier
     * @param alg Algorithm which port is connected to the port of this algorithm
     * @param algPortIdentifier Identifier of the port of alg
     * @param thisPortIdentifier Identifier of the port of this algorithm
     */
    void connect(Algorithm* alg, const std::string& algPortIdentifier,
            const std::string& thisPortIdentifier);

    /** Set the parameters
     * @param param The Parameters where paramters are set to.
     */
    void setParameters(const libpipe::utilities::Parameters& param);

protected:
    /** Constructor.
     */
    Algorithm();

    /** Map of the ports and their \c std::string Identifier
     */
    std::map<std::string, boost::shared_ptr<Data> > ports_;

    /** Stores the parameters needed by the update methode of the algorithm
     */
    libpipe::utilities::Parameters parameters_;

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
#ifdef ENABLE_THREADING
    /** Mutex for the algorithm class to make sure only one thread at a time is
     * calling update methode from processRequest
     */
    boost::mutex processRequestMutex_;

    /** Mutex to secure ports_
     */
    mutable boost::shared_mutex portMutex_;

    /** Mutex to secure mTime_
     */
    mutable boost::shared_mutex mTimeMutex_;
#endif

};
} // namespace rtc
} // namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_RTC_ALGORITHM_HPP__
