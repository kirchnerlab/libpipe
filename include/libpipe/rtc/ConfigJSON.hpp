/*
 * ConfigJSON.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGJSON_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGJSON_HPP__

#include <libpipe/config.hpp>

#include <libpipe/rtc/Config.hpp>

#include <list>
#include <string>
#include <queue>

namespace libpipe {
namespace rtc {

class ConfigJSON : public Config
{
    public:

        /** Constructor
         */
        ConfigJSON();

        /** Destructor
         */
        ~ConfigJSON();

        /** Parses the input files.
         * \li 1. file: Filter Configuration
         * \li 2. file: Connection Configurations
         * \li 3. file: Pipeline configuration
         * @param filename Names of the input files
         */
        virtual void parseInputFile(const std::vector<std::string>& filename);

        /** Gives a list of all Filters that need to be generated
         * @return A list of Filters
         */
        virtual const std::list<FilterDescription>& getFilters() const;

        /**
         * @param filtername The name of the Filter, which manager get connected to the Precursors
         * @return List of Precursors Filter filtername gets connected to
         */
        virtual const std::list<PrecursorDescription>& getPrecursorFilter(
            const std::string& filtername) const;

        /**
         * @param filtername The name of the Filter which ports are returned
         * @return list of all ports one Filter is connected to
         */
        virtual const std::list<PortDescription>& getPort(
            const std::string& filtername) const;

        /**
         *
         * @return A priority_queue where all elements are ordered after their request rank,
         * the smallest comes first
         */
        virtual std::priority_queue<PipelineDescription,
                std::vector<PipelineDescription>, PipelineDescriptionLess> getLibpipePipe() const;

        /** Checks the input files. Order is important!
         * @param filename Names of the input files
         */
        virtual bool checkFile(const std::vector<std::string>& filename) const;

    private:

        std::list<FilterDescription> filterList_;

        std::priority_queue<PipelineDescription,
                std::vector<PipelineDescription>, PipelineDescriptionLess> requestQueue_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGJSON_HPP__ */
