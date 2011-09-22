/*
 * Filter.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner 
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_FILTER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_FILTER_HPP__

#include <libpipe/config.hpp>
#include <string>
#include <libpipe/NonCopyable.hpp>
#include <libpipe/Request.hpp>

namespace libpipe {

// forward declarations
class Algorithm;
class Manager;

/** The base class for all LIBPIPE filters. Filters are non-copyable by
 * default.
 */
class Filter : private NonCopyable
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
    virtual Algorithm* getAlgorithm();

    /** Returns a  pointer to the Manager object.
     * @return A pointer to the Manager object.
     */
    virtual Manager* getManager();

    /** Returns the name of the filter.
     * @return The name of the fitler.
     */
    std::string getName() const;

    /** Set the name of the filter.
     * @param[in] name The name of the filter.
     */
    void setName(const std::string& name);

protected:
    /** Set the algorithm that should be used for this filter.
     * @param[in] alg Pointer to the Algorithm object.
     */
    void setAlgorithm(Algorithm* alg);

    /** Set the manager that manages the filter.
     * @param[in] manager Pointer to the Manager object.
     */
    void setManager(Manager* manager);

private:
    /** A pointer to the algorithm that is part of the filter.
     */
    Algorithm* algorithm_;

    /** A pointer to the manager that is part of the filter.
     */
    Manager* manager_;

    /** Holds the name of the filter.
     */
    std::string name_;
};

} // namespace libpipe

#endif

