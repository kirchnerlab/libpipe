/*
 * Filter.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner 
 *               2011 David Sichau
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_FILTER_RTC_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_FILTER_RTC_HPP__

#include <libpipe/config.hpp>
#include <string>
#include <libpipe/NonCopyable.hpp>
#include <libpipe/Request.hpp>

namespace libpipe {
namespace rtc {

// forward declarations
class Algorithm;
class Manager;

/** The only class for all LIBPIPE runtime configuration filters. Filters are non-copyable by
 * default. You should not inherit from this class.
 */
class Filter : private NonCopyable
{
    public:

        /** static create Methode to generate Filters
         * @param name Name of the Filter
         * @param algorithmName Identifier of the Algorithm used.
         * @param managerName Identifier of the Manager used
         * @return a new Instance of Filter
         */
        static Filter* create(const std::string& name,
            const std::string& algorithmName, const std::string& managerName);

        /** Destructor of class Filter it will releas the memory for the algorithm and manager the filter contains
         */
        ~Filter();

        /** Processes a request.
         * This method forwards the request to the Algorithm and Manager objects.
         * @param[in] req The request object.
         * @return The request object with processing information filled out.
         */
        Request& processRequest(Request& req);

        /** Returns a  pointer to the algorithm object.
         * @return A pointer to the algorithm object.
         */
        Algorithm* getAlgorithm();

        /** Returns a  pointer to the Manager object.
         * @return A pointer to the Manager object.
         */
        Manager* getManager();

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
         * @param algorithm Pointer to the Algorithm that the filter will uses
         * @param manager Pointer to the Manager that the filter will uses
         */
        Filter(const std::string& name, Algorithm* algorithm,
            Manager* manager);
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

        /** Holds the name of the filter.
         */
        std::string name_;

};

} // namespace rtc
} // namespace libpipe

#endif
