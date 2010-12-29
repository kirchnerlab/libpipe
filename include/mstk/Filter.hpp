/*
 * Filter.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner 
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_FILTER_HPP__
#define __MSTK_INCLUDE_MSTK_FILTER_HPP__

#include <mstk/config.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <mstk/Request.hpp>

namespace mstk {

// forward declarations
class Algorithm;
class Manager;

/** The base class for all MSTK filters.
 */
class Filter
{
  public:
    /** Convenience typedef. */
    typedef boost::shared_ptr<Algorithm> AlgorithmPtr;
    typedef boost::shared_ptr<Manager> ManagerPtr;

    /** Pure virtual destructor.
     */
    virtual ~Filter() = 0;
    
    /** Processes a request.
     * This method forwards the request to the Algorithm and Manager objects.
     * @param[in] req The request object.
     * @return The request object with processing information filled out.
     */
    virtual Request& processRequest(Request& req);
    
    /** Returns a  pointer to the algorithm object.
     * @return A pointer to the algorithm object.
     */
    AlgorithmPtr getAlgorithm();

    /** Returns a  pointer to the Manager object.
     * @return A pointer to the Manager object.
     */
    ManagerPtr getManager();

  protected:
    /** Set the algorithm that should be used for this filter.
     * The filter takes posession of the pointer. The client should hence never
     * attempt to delete the Algorithm instance, once it has been passed.
     * @param[in] Smart pointer to the Algorithm object.
     */
    void setAlgorithm(AlgorithmPtr alg);
    
    /** Set the manager that manages the filter.
     * The filter takes posession of the object.
     * @param[in] manager Smart pointer to the Manager object.
     */
    void setManager(ManagerPtr manager);

    AlgorithmPtr algorithm_;
    ManagerPtr manager_;
    
};

} // namespace mstk

#endif

