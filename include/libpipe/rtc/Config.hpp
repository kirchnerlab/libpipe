/*
 * Config.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIG_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIG_HPP__

#include <libpipe/config.hpp>

#include <string>
#include <list>
#include <map>
#include <functional>
#include <queue>

namespace libpipe {
namespace rtc {

/**
 * All information needed to connect the ports.
 */
struct PortDescription
{
        /** Name of the filter which output port is used
         */
        std::string filterName;
        /** Name of the output port
         */
        std::string portNameOfFilter;
        /** Name of the input port of this filter
         */
        std::string portNameOfThis;
};

/**
 * The information needed to connect the managers
 */
struct PrecursorDescription
{
        /** Name of the precursor Filter
         */
        std::string precursorName;
};

/**
 * The information needed to generate filters and connect their algorithms and managers
 */
struct FilterDescription
{
        /** Name of the filter
         */
        std::string filterName;
        /** Name of the filters algorithm
         */
        std::string algorithmName;
        /** Name of the filters manager
         */
        std::string managerName;

        /** List of precursors the filters manager is connected to
         */
        std::list<PrecursorDescription> precursors;

        /** List of ports the filters algorithm is connected to
         */
        std::list<PortDescription> ports;
};

/**
 * The information needed to build the libpipe pipeline
 */
struct PipelineDescription
{
        /** Name of the filter
         */
        std::string filterName;
        /** Name of type of request
         */
        std::string requestType;
        /** Boolean flag which will be true if a trace should be generated
         */
        bool makeTrace;
        /** rank of the request, the higher the later it will be carried out
         */
        unsigned int requestRank;
};

/**
 * Comparison function to compare two LibpipePipeStructs
 */
///\cond
struct PipelineDescriptionLess : public std::binary_function<
        PipelineDescription, PipelineDescription, bool>
{
        ///\endcond
        /** less than operator
         * @param lhs lefthand side LibpipePipeStruct
         * @param rhs righthand side LibpipePipeStruct
         * @return true if lhs < rhs
         */
        bool operator ()(const PipelineDescription& lhs,
            PipelineDescription& rhs) const;
};

class Config
{
    public:

        /** Virtual Destructor to allow inheritance.
         *
         */
        virtual ~Config() = 0;

        /** Parses the input files. Order is important!
         * @param filename Names of the input files. Identifed by a string key
         */
        virtual void parseInputFile(const std::map<std::string, std::string>& filename) = 0;

        /** Gives a list of all Filters that need to be generated
         * @return A list of Filters
         */
        virtual const std::list<FilterDescription>& getFilters() const = 0;

        /**
         * @param filtername The name of the Filter, which manager get connected to the Precursors
         * @return List of Precursors Filter filtername gets connected to
         */
        virtual const std::list<PrecursorDescription>& getPrecursorFilter(
            const std::string& filtername) const = 0;

        /**
         * @param filtername The name of the Filter which ports are returned
         * @return list of all ports one Filter is connected to
         */
        virtual const std::list<PortDescription>& getPort(
            const std::string& filtername) const = 0;

        /**
         * @return A priority_queue where all elements are ordered after their request rank,
         * the smallest comes first
         */
        virtual std::priority_queue<PipelineDescription,
                std::vector<PipelineDescription>, PipelineDescriptionLess> getLibpipePipe() const=0;

        /** Checks the input files. Order is important!
         * @param filename Names of the input files. Identified by a string key.
         */
        virtual bool checkFile(const std::map<std::string, std::string>& filename) const = 0;

};

} /* namespace rtc */
} /* namespace libpipe */

#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIG_HPP__ */
