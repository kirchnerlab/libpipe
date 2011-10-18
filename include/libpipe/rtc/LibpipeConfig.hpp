/*
 * LibpipeConfig.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPECONFIG_HPP_
#define LIBPIPECONFIG_HPP_

#include <string>
#include <list>
#include <functional>
#include <queue>

namespace libpipe {
namespace rtc {

/**
 * All information needed to connect the ports.
 */
struct PortStruct
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
struct PrecursorStruct
{
        /** Name of the precursor Filter
         */
        std::string precursorName;
};

/**
 * The information needed to generate filters and connect their algorithms and managers
 */
struct FilterStruct
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
        std::list<PrecursorStruct> precursors;

        /** List of ports the filters algorithm is connected to
         */
        std::list<PortStruct> ports;
};

/**
 * The information needed to build the libpipe pipeline
 */
struct LibpipePipeStruct
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
struct LibpipePipeStructLess : public std::binary_function<LibpipePipeStruct,
        LibpipePipeStruct, bool>
{
        ///\endcond
        /** less than operator
         * @param lhs lefthand side LibpipePipeStruct
         * @param rhs righthand side LibpipePipeStruct
         * @return true if lhs < rhs
         */
        bool operator ()(const LibpipePipeStruct& lhs,
            LibpipePipeStruct& rhs) const
        {
            return lhs.requestRank < rhs.requestRank;
        }
};

class LibpipeConfig
{
    public:

        /** create Methode which is registered in the InputFactory
         * @return Pointer to the new generated Libconfig class, keep in mind to call delete on this generated pointer
         */
        static LibpipeConfig* create();

        /** Virtual Destructor to allow inheritance.
         *
         */
        virtual ~LibpipeConfig()
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
        virtual std::list<FilterStruct> const& getFilters() const = 0;

        /**
         * @param filtername The name of the Filter, which manager get connected to the Precursors
         * @return List of Precursors Filter filtername gets connected to
         */
        virtual std::list<PrecursorStruct> const& getPrecursorFilter(
            std::string const& filtername) const = 0;

        /**
         * @param filtername The name of the Filter which ports are returned
         * @return list of all ports one Filter is connected to
         */
        virtual std::list<PortStruct> const& getPort(
            std::string const& filtername) const = 0;

        /**
         * @return A priority_queue where all elements are ordered after their request rank,
         * the smallest comes first
         */
        virtual std::priority_queue<LibpipePipeStruct,
                std::vector<LibpipePipeStruct>, LibpipePipeStructLess> getLibpipePipe() const=0;

        /** Checks if the file is correct
         * @return True if the file is correct, otherwise false
         */
        virtual bool checkFile() const =0;

    protected:
        /** Constructor
         */
        LibpipeConfig()
        {
        }
        ;

};

} /* namespace rtc */
} /* namespace libpipe */

#endif /* LIBPIPECONFIG_HPP_ */
