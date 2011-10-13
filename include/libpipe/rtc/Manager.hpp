/*

 * Manager.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_MANAGER_RTC_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_MANAGER_RTC_HPP__

#include <libpipe/config.hpp>
#include <set>
#include <libpipe/Request.hpp>
#include <libpipe/NonCopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <libpipe/rtc/LibpipeFactories.hpp>

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
class Manager : private libpipe::NonCopyable
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
         * @param[in] req The request object, non-const (good for e.g. adding trace
         *                information)
         * @return The (potentially modified) request object.
         */
        virtual Request& processRequest(Request& req);

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
         * @param[inout] f Pointer to a filter object on which the current manager
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

        /** Register Filter in the FilterFactory
         *
         */
        static const bool registered_;

        static const bool registerLoader();

    private:
        /** Returns the Filter Manager is dependent on
         * @return A Set of shared_ptr to Filters
         */
        std::set<boost::shared_ptr<Filter> > getSources();
};

} // namespace rtc
} // namespace libpipe

#endif
