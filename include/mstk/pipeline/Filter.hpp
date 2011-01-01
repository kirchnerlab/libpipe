/*
 * Filter.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner 
 *
 */
#ifndef __MSTK_INCLUDE_MSTK_FILTER_HPP__
#define __MSTK_INCLUDE_MSTK_FILTER_HPP__

#include <mstk/config.hpp>
#include <string>
#include <mstk/pipeline/Request.hpp>

namespace mstk {

// forward declarations
class Algorithm;
class Manager;

/** The base class for all MSTK filters.
 */
class Filter
{
  public:
    /** Constructor.
     */
    Filter(const std::string&);

    /** Pure virtual destructor.
     */
    virtual ~Filter();
    
    /** Processes a request.
     * This method forwards the request to the Algorithm and Manager objects.
     * @param[in] req The request object.
     * @return The request object with processing information filled out.
     */
    virtual Request& processRequest(Request& req);
    
    /** Returns a  pointer to the algorithm object.
     * @return A pointer to the algorithm object.
     */
    virtual Algorithm* getAlgorithm() = 0;

    /** Returns a  pointer to the Manager object.
     * @return A pointer to the Manager object.
     */
    virtual Manager* getManager() = 0;
    
    /** Returns the name of the filter.
     * @return The name of the fitler.
     */
    std::string getName() const;

  protected:
    /** Set the algorithm that should be used for this filter.
     * @param[in] alg Pointer to the Algorithm object.
     */
    void setAlgorithm(Algorithm* alg);
    
    /** Set the manager that manages the filter.
     * @param[in] manager Pointer to the Manager object.
     */
    void setManager(Manager* manager);


    /** A pointer to the algorithm that is part of the filter.
     */
    Algorithm* algorithm_;

    /** A pointer to the manager that is part of the filter.
     */
    Manager* manager_;

  private:
    /** Holds the name of the filter.
     */
    std::string name_;
};

} // namespace mstk

#endif

