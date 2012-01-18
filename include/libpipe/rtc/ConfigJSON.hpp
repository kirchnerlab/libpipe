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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGJSON_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGJSON_HPP__

#include <libpipe/config.hpp>

#include <libpipe/rtc/Config.hpp>

#include <list>
#include <string>
#include <queue>

namespace libpipe {
namespace rtc {

/** ConfigJSON Class for loading the configuration from JSON files
 * @ingroup rtc
 */
class LIBPIPE_EXPORT ConfigJSON : public Config
{
public:

    /** Constructor
     */
    ConfigJSON();

    /** Destructor
     */
    ~ConfigJSON();

    /** Parses the input files.
     * \li key: "FilterInput" Input file with the Filter Configuration
     * \li key: "ConnectionInput" Input file with the Connection Configurations
     * \li key: "PipelineInput" Input file with the Pipeline configuration
     * @param filename Names of the input files
     */
    virtual void parseInputFile(
            const std::map<std::string, std::string>& filename);

    /** Gives a list of all Filters that need to be generated
     * @return A list of Filters
     */
    virtual const std::list<FilterDescription>& getFilters() const;

    /** Returns the precursor Filters
     * @param filtername The name of the Filter, which manager get connected to the Precursors
     * @return List of Precursors Filter filtername gets connected to
     */
    virtual const std::list<PrecursorDescription>& getPrecursorFilter(
            const std::string& filtername) const;

    /** Returns the ports
     * @param filtername The name of the Filter which ports are returned
     * @return list of all ports one Filter is connected to
     */
    virtual const std::list<PortDescription>& getPort(
            const std::string& filtername) const;

    /** Returns the libpipe Pipeline
     * @return A priority_queue where all elements are ordered after their request rank,
     * the smallest comes first
     */
    virtual std::priority_queue<PipelineDescription,
    std::vector<PipelineDescription>, PipelineDescriptionLess> getLibpipePipe() const;

    /** Checks the input files. Order is important!
     * @param filename Names of the input files
     * @return true if the file is correct
     */
    virtual bool checkFile(
            const std::map<std::string, std::string>& filename) const;

private:

    /** List of Filters descriptions
     */
    std::list<FilterDescription> filterList_;
    /** Pipeline of request informations
     */
    std::priority_queue<PipelineDescription,
    std::vector<PipelineDescription>, PipelineDescriptionLess> requestQueue_;

};

} /* namespace rtc */
} /* namespace libpipe */
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_RTC_CONFIGJSON_HPP__ */
