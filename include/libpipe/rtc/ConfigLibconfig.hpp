/*
 * ConfigLibconfig.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGLIBCONFIG_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGLIBCONFIG_HPP__

#include <libpipe/config.hpp>


#include <libpipe/rtc/Config.hpp>

#include <list>
#include <string>
#include <queue>

namespace libpipe {
namespace rtc {

class ConfigLibconfig : public Config
{
    public:

        /** Constructor
         */
        ConfigLibconfig();

        /** Destructor
         */
        ~ConfigLibconfig();

        /** Parses the input file.
         * @param inputFileName Name of the input file.
         */
        virtual void parseInputFile(std::string const& inputFileName);

        /** Gives a list of all Filters that need to be generated
         * @return A list of Filters
         */
        virtual std::list<FilterDescription> const& getFilters() const;

        /**
         * @param filtername The name of the Filter, which manager get connected to the Precursors
         * @return List of Precursors Filter filtername gets connected to
         */
        virtual std::list<PrecursorDescription> const& getPrecursorFilter(
            std::string const& filtername) const;

        /**
         * @param filtername The name of the Filter which ports are returned
         * @return list of all ports one Filter is connected to
         */
        virtual std::list<PortDescription> const& getPort(
            std::string const& filtername) const;

        /**
         *
         * @return A priority_queue where all elements are ordered after their request rank,
         * the smallest comes first
         */
        virtual std::priority_queue<PipelineDescription,
                std::vector<PipelineDescription>, PipelineDescriptionLess> getLibpipePipe() const;

        /** Checks if the file is correct
         * @return True if the file is correct, otherwise false
         */
        virtual bool checkFile(const std::string& inputFileName) const;

    private:

        std::list<FilterDescription> filterList_;

        std::priority_queue<PipelineDescription, std::vector<PipelineDescription>,
                PipelineDescriptionLess> requestQueue_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGLIBCONFIG_HPP__ */
