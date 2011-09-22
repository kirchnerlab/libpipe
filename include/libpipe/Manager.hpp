/*
 * Manager.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_MANAGER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_MANAGER_HPP__

#include <libpipe/config.hpp>
#include <set>
#include <libpipe/Request.hpp>
#include <libpipe/NonCopyable.hpp>

namespace libpipe {

// forward declaration
class Algorithm;
class Filter;

/** Base class for Managers.
 * Managers are wrapped with Algorithms to form the filters of the pipeline.
 * While the filters provide all data processing capabilities, the managers
 * link the components of the pipeline and make sure that filters get executed
 * in the correct order.
 */
class Manager : private NonCopyable
{
public:
    /** Constructor.
     */
    Manager();

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
     *  
     * @param[inout] f Pointer to a filter object on which the current manager
     *                 should depend.
     */
    void connect(Filter* f);

protected:
    /** Convenience typedef: a filter set.
     */
    typedef std::set<Filter*> FilterSet;

    /** The set of filters the manager depends on.
     */
    FilterSet sources_;

    /** Pointer to the algorithm that is managed by the manager.
     */
    Algorithm* algorithm_;
};

} // namespace libpipe

#endif

