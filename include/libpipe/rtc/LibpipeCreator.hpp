/*
 * LibpipeCreator.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPECREATOR_HPP_
#define LIBPIPECREATOR_HPP_

#include <map>

#include "libpipe/rtc/Filter.hpp"
#include "libpipe/rtc/LibpipePipeline.hpp"
#include "libpipe/NonCopyable.hpp"

#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {

class LibpipeConfig;

/** Generates the objects needed by libpipe, it only relies on the LibpipeConfig interface. And
 * not on the input file.
 */
class LibpipeCreator : public libpipe::NonCopyable
{
    public:

        /** Constructor
         * @param filename The name to the configuration file
         */
        LibpipeCreator(std::string const& filename);

        /** Destructor
         */
        ~LibpipeCreator();

        /** Returns a shared pointer to the requested Filter, throw an exception
         * if the filter is not found
         * @param filtername The name of the filter one looks for
         * @return A shared_ptr to a Filter Object
         */
        boost::shared_ptr<Filter> getFilter(std::string const& filtername);

        /** Returns a LibpipePipeline object, where all information is stored to
         * run libpipe.
         * @return Reference to a LibpipePipeline.
         */
        LibpipePipeline const& getPipeline() const;

    private:
        /** Pointer to the configuration.
         */
        LibpipeConfig* configuration_;

        /** This function will generate the filter objects.
         */
        void generateFilters();

        /** This function will connect the managers.
         * @param filtername Name of the filter
         */
        void connectManagers(std::string const& filtername);

        /** This function will connect the ports of the algorithms.
         *  @param filtername Name of the filter
         */
        void connectAlgorithmPorts(std::string const& filtername);

        /** This function will generate the pipeline object
         */
        void generatePipeline();

        /** Typedef of FilterMap
         */
        typedef std::map<std::string, boost::shared_ptr<Filter> > FilterMap;

        /** Map of the filters identified by their string
         */
        FilterMap filterMap_;

        /** The pipeline object
         */
        LibpipePipeline pipeline_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* LIBPIPECREATOR_HPP_ */
