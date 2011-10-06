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
#include <libpipe/LibpipeFactories.hpp>

namespace libpipe_rtc {

// forward declarations
class AlgorithmRTC;
class ManagerRTC;

/** The base class for all LIBPIPE filters. Filters are non-copyable by
 * default.
 */
class FilterRTC : private libpipe::NonCopyable
{
    public:

        static FilterRTC* create(const std::string& name,
            const std::string& algorithmName, const std::string& managerName);

        /** Pure virtual destructor.
         */
        virtual ~FilterRTC();

        /** Processes a request.
         * This method forwards the request to the Algorithm and Manager objects.
         * @param[in] req The request object.
         * @return The request object with processing information filled out.
         */
        virtual libpipe::Request& processRequest(libpipe::Request& req);

        /** Returns a  pointer to the algorithm object.
         * @return A pointer to the algorithm object.
         */
        virtual AlgorithmRTC* getAlgorithm();

        /** Returns a  pointer to the Manager object.
         * @return A pointer to the Manager object.
         */
        virtual ManagerRTC* getManager();

        /** Returns the name of the filter.
         * @return The name of the filter.
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
        void setAlgorithm(AlgorithmRTC* alg);

        /** Set the manager that manages the filter.
         * @param[in] manager Pointer to the Manager object.
         */
        void setManager(ManagerRTC* manager);

    private:
        /** Constructor.
         * @param name The name of the filter.
         * @param algorithmName The name of the Algorithm that will be generated
         * @param managerName The name of the Manager that will be generated
         */
        FilterRTC(const std::string& name, const std::string& algorithmName,
            const std::string& managerName);

        /** A pointer to the algorithm that is part of the filter.
         */
        AlgorithmRTC* algorithm_;

        /** A pointer to the manager that is part of the filter.
         */
        ManagerRTC* manager_;

        /** Holds the name of the filter.
         */
        std::string name_;
        /** Register Filter in the FilterFactory
         *
         */
        static const bool registered_;

        static const bool registerLoader()
        {
            std::string ids = "FilterRTC";
            return FilterFactory::instance().registerType(ids,
                FilterRTC::create);
        }
};

const bool FilterRTC::registered_ = registerLoader();

} // namespace libpipe

#endif

