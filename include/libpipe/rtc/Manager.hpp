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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_MANAGER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_MANAGER_HPP__

#include <libpipe/config.hpp>

#include <set>

#include <libpipe/Request.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/noncopyable.hpp>
#ifdef ENABLE_THREADING
#include <boost/thread.hpp>
#endif

namespace libpipe {
namespace rtc {

// forward declaration
class Algorithm;
class Filter;

/** Base class for runtime configuration Managers.
 * Managers are wrapped with Algorithms to form the filters of the pipeline.
 * While the filters provide all data processing capabilities, the managers
 * link the components of the pipeline and make sure that filters get executed
 * in the correct order.
 */
class LIBPIPE_EXPORT Manager : boost::noncopyable
{
    public:

        /** create Methode for manager which is called by ManagerFactory
         * @return A Pointer to the new generated Manager, keep in mind that you are responsible for deleting the pointer after usage
         */
        static Manager* create();

        /** Destructor.
         */
        virtual ~Manager();

        /** Get a pointer to the algorithm object currently managed by the manager.
         * @return A pointer to an algorithm object (or 0).
         */
        Algorithm* getAlgorithm();

        /** Set the algorithm that is managed by the manager.
         * @param[in] alg Pointer to the algorithm object.
         */
        void setAlgorithm(Algorithm* alg);

        /** Process a processing request. In the simple base class implementation
         * the manager will call the \c process request method of all filters
         * it depends on and will subsequently execute its own algorithm.
         *
         * @param[in,out] req The request object, non-const (good for e.g. adding trace
         *                information)
         */
        virtual void processRequest(libpipe::Request& req);

        /** Connect the manager to a filter it depends on. Each call connects the
         * Manager to the specified filter; duplicates will be ignored.
         * Because of the use of shared_pointers one need to dynamically cast the
         * pointers to boost::shared_ptr<Filter> this can be done with the use of
         * boost::dynamic_pointer_cast<Filter>
         * \code
         * ...
         * boost::shared_ptr<UserFilter> uf (new UserFilter("FilterName"));
         * ...
         * uf->getManager()->connect(boost::dynamic_pointer_cast<Filter>(someOtherFilter->getManager()));
         * \endcode
         *
         * @param [in,out] f Pointer to a filter object on which the current manager
         *                 should depend.
         */
        void connect(boost::shared_ptr<Filter> f);

    protected:

        /** Constructor.
         */
        Manager();

        /** Convenience typedef: a filter set.
         */
        typedef std::set<boost::shared_ptr<Filter> > FilterSet;

        /** The set of filters the manager depends on.
         */
        FilterSet sources_;

        /** Pointer to the algorithm that is managed by the manager.
         */
        Algorithm* algorithm_;

        /** Disconnects the manager from all his input filters.
         * The Algorithm calls does at the same time fix the output
         * of the corresponding Algorithm, so that the output will
         * stay constant.
         *
         */
        void disconnect();

    private:
        /** Returns the Filter Manager is dependent on
         * @return A Set of shared_ptr to Filters
         */
        std::set<boost::shared_ptr<Filter> > getSources();
        /** Register Filter in the FilterFactory
         *
         */
        static const bool registered_;

        /** Registers the manager in the managerfactory
         * @return true if successful
         */
        static const bool registerLoader();
#ifdef ENABLE_THREADING
        /** Mutex for the processRequest
         */
        boost::mutex processRequestMutex_;
        /** Mutex for the algorithm_
         */
        boost::shared_mutex algorithmMutex_;
        /** Mutex for the source_
         */
        boost::shared_mutex sourcesMutex_;
#endif

};

} // namespace rtc
} // namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_RTC_MANAGER_HPP__
