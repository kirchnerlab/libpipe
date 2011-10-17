/*
 * LibpipeConfigLibconfig.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPECONFIGLIBCONFIG_HPP_
#define LIBPIPECONFIGLIBCONFIG_HPP_
#include "LibpipeConfig.hpp"

#include <list>
#include <string>
#include <queue>


namespace libpipe {
namespace rtc {

class LibpipeConfigLibconfig : public LibpipeConfig
{
    public:

        LibpipeConfigLibconfig(std::string const& fileName);

        virtual ~LibpipeConfigLibconfig();

        /** Gives a list of all Filters that need to be generated
         * @return A list of Filters
         */
        virtual std::list<FilterStruct> const& getFilters() const;

        /**
         * @param filtername The name of the Filter, which manager get connected to the Precursors
         * @return List of Precursors Filter filtername gets connected to
         */
        virtual std::list<PrecursorStruct> const& getPrecursorFilter(
            std::string const& filtername) const;

        /**
         * @param filtername The name of the Filter which ports are returned
         * @return list of all ports one Filter is connected to
         */
        virtual std::list<PortStruct> const& getPort(
            std::string const& filtername) const;

        /**
         *
         * @return A priority_queue where all elements are ordered after their request rank,
         * the smallest comes first
         */
        virtual std::priority_queue<LibpipePipeStruct,
                std::vector<LibpipePipeStruct>, LibpipePipeStructLess> getLibpipePipe() const;

    private:

        void parseInputFile(std::string const& inputFileName);

        std::list<FilterStruct> filterList_;

        std::priority_queue<LibpipePipeStruct,
                        std::vector<LibpipePipeStruct>, LibpipePipeStructLess> requestQueue_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* LIBPIPECONFIGLIBCONFIG_HPP_ */
