/*
 * LibpipeConfigLibconfig.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPECONFIGLIBCONFIG_HPP_
#define LIBPIPECONFIGLIBCONFIG_HPP_
#include "libpipe/rtc/Config.hpp"

#include <list>
#include <string>
#include <queue>

namespace libpipe {
namespace rtc {

class LibpipeConfigLibconfig : public Config
{
    public:

        /** Constructor
         */
        LibpipeConfigLibconfig();

        /** Destructor
         */
        ~LibpipeConfigLibconfig();

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
        virtual bool checkFile() const;

    private:

        std::list<FilterDescription> filterList_;

        std::priority_queue<PipelineDescription, std::vector<PipelineDescription>,
                PipelineDescriptionLess> requestQueue_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* LIBPIPECONFIGLIBCONFIG_HPP_ */
