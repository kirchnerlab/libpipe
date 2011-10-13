/*
 * LibpipeConfig.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPECONFIG_HPP_
#define LIBPIPECONFIG_HPP_

namespace libpipe {
namespace rtc {

struct PortStruct
{
        std::string filterName;
        std::string portNameOfFilter;
        std::string portNameOfThis;
};

struct PrecursorStruct
{
        std::string precursorName;
};

struct FilterStruct
{
        std::string filterName;
        std::string algorithmName;
        std::string managerName;
        std::list<PrecursorStruct> precursors;
        std::list<PortStruct> ports;
};

class LibpipeConfig
{

    public:
        /** Constructor
         * @param filepath Filepath to the configuration file
         */
        LibpipeConfig();

        virtual ~LibpipeConfig()
        {
        }
        ;


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
        virtual std::list<PortStruct> const& getPort(std::string const& filtername) const = 0;

};

} /* namespace rtc */
} /* namespace libpipe */

#endif /* LIBPIPECONFIG_HPP_ */
