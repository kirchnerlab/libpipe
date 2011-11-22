/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2010 Marc Kirchner
*
* This file is part of libpipe.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONTROLER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONTROLER_HPP__

#include <libpipe/config.hpp>

#include <map>

#include <libpipe/rtc/Filter.hpp>
#include <libpipe/rtc/Pipeline.hpp>

#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {


/// \cond
class LIBPIPE_EXPORT Config;
/// \endcond

/** Generates the objects needed by libpipe, it only relies on the Config interface. And
 * not on the input file.
 * @ingroup rtc
 */
class PipelineLoader
{
    public:

        /** Constructor
         * @param filename The names to the configurations file. Identified by a string key.
         */
        PipelineLoader(const std::map<std::string, std::string>& filename);

        /** Destructor
         */
        ~PipelineLoader();

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
