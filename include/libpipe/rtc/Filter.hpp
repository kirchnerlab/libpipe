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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_FILTER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_FILTER_HPP__

#include <libpipe/config.hpp>

#include <string>

#include <libpipe/Request.hpp>

#include <boost/noncopyable.hpp>
#include <boost/exception_ptr.hpp>

#ifdef ENABLE_THREADING
#include <boost/thread.hpp>
#endif

namespace libpipe {
namespace rtc {

// forward declarations
class Algorithm;
class Manager;

/** A filter that supports runtime configuration.
 * Filters are non-copyable composite objects that combine a \c Manager and
 * an \c Algorithm object. Note that the \c Filter
 * destructor is not virtual, that \c Filter is hence not designed to
 * serve as a base class and that extension of filter functionalities
 * should be implemented by extending its constituents, i.e.
 * \c Algorithm and \c Manager.
 * @ingroup rtc
 */
class LIBPIPE_EXPORT Filter : boost::noncopyable
{
public:

    /** Filter factory method.
     * @param name Unique name of the filter.
     * @param algorithmName String that uniquely identifies an algorithm type.
     * @param managerName String that uniquely identifies a manager type.
     * @return A pointer to a new \c Filter instance.
     */
    static Filter* create(const std::string& name,
            const std::string& algorithmName, const std::string& managerName);

    /** Destructor.
     */
    ~Filter();

#ifdef ENABLE_THREADING
    /** Processes a request.
     * This simply forwards the request to the Algorithm and Manager objects.
     * @param[in] req The request object.
     * @param[out] error Pointer to an active exception (in the multithreading
     *                   code only).
     */
    void processThreadedRequest(libpipe::Request req,
            boost::exception_ptr & error);
#endif

    /** Processes a request.
     * This simply forwards the request to the Algorithm and Manager objects.
     * @param[in,out] req The request object.
     */
    void processRequest(libpipe::Request& req);

    /** Returns a  pointer to the algorithm object.
     * @return A pointer to the algorithm object.
     */
    Algorithm* getAlgorithm() const;

    /** Returns a  pointer to the Manager object.
     * @return A pointer to the Manager object.
     */
    Manager* getManager() const;

    /** Returns the name of the filter.
     * @return The name of the filter.
     */
    std::string getName() const;

    /** Set the name of the filter.
     * @param[in] name The name of the filter.
     */
    void setName(const std::string& name);

private:
    /** Constructor.
     * @param name The name of the filter.
     * @param algorithm Pointer to the \c Algorithm instance.
     * @param manager Pointer to the \c Manager instance.
     */
    Filter(const std::string& name, Algorithm* algorithm,
            Manager* manager);

    /** Set the algorithm that should be used for this filter.
     * @param[in] alg Pointer to the \c Algorithm object.
     */
    void setAlgorithm(Algorithm* alg);

    /** Set the manager that manages the filter.
     * @param[in] manager Pointer to the \c Manager object.
     */
    void setManager(Manager* manager);

    /** Pointer to the algorithm that is part of the filter.
     */
    Algorithm* algorithm_;

    /** Pointer to the manager that is part of the filter.
     */
    Manager* manager_;

    /** The name of the filter.
     */
    std::string name_;

    /** Mutex for the name_
     */
    mutable boost::shared_mutex nameMutex_;

    /** Mutex for the algorithm_
     */
    mutable boost::shared_mutex algorithmMutex_;

    /** Mutex for the manager_
     */
    mutable boost::shared_mutex managerMutex_;
};

} // namespace rtc
} // namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_RTC_FILTER_HPP__
