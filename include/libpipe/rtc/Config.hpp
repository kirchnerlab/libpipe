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
struct PipelineDescriptionLess : public std::binary_function<PipelineDescription,
        PipelineDescription, bool>
{
        ///\endcond
        /** less than operator
         * @param lhs lefthand side LibpipePipeStruct
         * @param rhs righthand side LibpipePipeStruct
         * @return true if lhs < rhs
         */
        bool operator ()(const PipelineDescription& lhs,
            PipelineDescription& rhs) const
        {
            return lhs.requestRank < rhs.requestRank;
        }
};

class Config
{
    public:

        /** create Methode which is registered in the InputFactory
         * @return Pointer to the new generated Libconfig class, keep in mind to call delete on this generated pointer
         */
        static Config* create();

        /** Virtual Destructor to allow inheritance.
         *
         */
        virtual ~Config()
        {
        }
        ;

        /** Parses the input file
         * @param inputFileName The name of the input file.
         */
        virtual void parseInputFile(std::string const& inputFileName) = 0;

        /** Gives a list of all Filters that need to be generated
         * @return A list of Filters
         */
        virtual std::list<FilterDescription> const& getFilters() const = 0;

        /**
         * @param filtername The name of the Filter, which manager get connected to the Precursors
         * @return List of Precursors Filter filtername gets connected to
         */
        virtual std::list<PrecursorDescription> const& getPrecursorFilter(
            std::string const& filtername) const = 0;

        /**
         * @param filtername The name of the Filter which ports are returned
         * @return list of all ports one Filter is connected to
         */
        virtual std::list<PortDescription> const& getPort(
            std::string const& filtername) const = 0;

        /**
         * @return A priority_queue where all elements are ordered after their request rank,
         * the smallest comes first
         */
        virtual std::priority_queue<PipelineDescription,
                std::vector<PipelineDescription>, PipelineDescriptionLess> getLibpipePipe() const=0;

        /** Checks if the file is correct
         * @return True if the file is correct, otherwise false
         */
        virtual bool checkFile(const std::string& inputFileName) const =0;


};

} /* namespace rtc */
} /* namespace libpipe */

#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIG_HPP__ */
