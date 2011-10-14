/*
 * LibpipeCreator.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#ifndef LIBPIPECREATOR_HPP_
#define LIBPIPECREATOR_HPP_

#include <map>

#include "Filter.hpp"
#include "libpipe/Exception.hpp"

#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {

class LibpipeConfig;

class LibpipeCreator
{
    public:
        /** Constructor
         * @param filepath The path to the configuration file
         */
        LibpipeCreator(std::string const& filepath);

        ~LibpipeCreator();

        /** Returns a shared pointer to the requested Filter, throw an exception
         * if the filter is not found
         * @param filtername The name of the filter one looks for
         * @return A shared_ptr to a Filter Object
         */
        boost::shared_ptr<Filter> getFilter(std::string const& filtername);



    private:
        LibpipeConfig* configuration_;

        void generateFilters();

        void connectManagers(std::string const& filtername);

        void connectAlgorithmPorts(std::string const& filtername);

        typedef std::map<std::string, boost::shared_ptr<Filter> > FilterMap;
        FilterMap filterMap_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* LIBPIPECREATOR_HPP_ */
