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
        virtual void parseInputFile(const std::string& inputFileName);

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
