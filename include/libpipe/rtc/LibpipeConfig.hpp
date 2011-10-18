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
        std::string filterName;
        std::string portNameOfFilter;
        std::string portNameOfThis;
};

/**
 * The information needed to connect the managers
 */
struct PrecursorStruct
{
        std::string precursorName;
};

/**
 * The information needed to generate filters and connect their algorithms and managers
 */
struct FilterStruct
{
        std::string filterName;
        std::string algorithmName;
        std::string managerName;
        std::list<PrecursorStruct> precursors;
        std::list<PortStruct> ports;
};

/**
 * The information needed to build the libpipe pipeline
 */
struct LibpipePipeStruct
{
        std::string filterName;
        std::string requestType;
        bool makeTrace;
        unsigned int requestRank;
};

/**
 * Comparison function to compare two LibpipePipeStructs
 */
struct LibpipePipeStructLess : public std::binary_function<LibpipePipeStruct,
        LibpipePipeStruct, bool>
{
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
        LibpipeConfig(){};

};

} /* namespace rtc */
} /* namespace libpipe */

#endif /* LIBPIPECONFIG_HPP_ */
