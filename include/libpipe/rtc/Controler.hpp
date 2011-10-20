/*
 * LibpipeCreator.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONTROLER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONTROLER_HPP__

#include <libpipe/config.hpp>

#include <map>

#include <libpipe/rtc/Filter.hpp>
#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/NonCopyable.hpp>

#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {

class Config;

/** Generates the objects needed by libpipe, it only relies on the Config interface. And
 * not on the input file.
 */
class Controler : public libpipe::NonCopyable
{
    public:

        /** Constructor
         * @param filename The name to the configuration file
         */
        Controler(const std::string& filename);

        /** Destructor
         */
        ~Controler();

        /** Returns a shared pointer to the requested Filter, throw an exception
         * if the filter is not found
         * @param filtername The name of the filter one looks for
         * @return A shared_ptr to a Filter Object
         */
        boost::shared_ptr<Filter> getFilter(const std::string& filtername);

        /** Returns a LibpipePipeline object, where all information is stored to
         * run libpipe.
         * @return Reference to a LibpipePipeline.
         */
        const Pipeline& getPipeline() const;

    private:
        /** Pointer to the configuration.
         */
        Config* configuration_;

        /** This function will generate the filter objects.
         */
        void generateFilters();

        /** This function will connect the managers.
         * @param filtername Name of the filter
         */
        void connectManagers(const std::string& filtername);

        /** This function will connect the ports of the algorithms.
         *  @param filtername Name of the filter
         */
        void connectAlgorithmPorts(const std::string& filtername);

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
        Pipeline pipeline_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONTROLER_HPP__ */
