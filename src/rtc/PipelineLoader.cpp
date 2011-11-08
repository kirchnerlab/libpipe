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

#include <libpipe/config.hpp>

#include <map>
#include <list>
#include <string>
#include <sstream>

#include <libpipe/rtc/Filter.hpp>
#include <libpipe/rtc/Manager.hpp>
#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/PipelineLoader.hpp>
#include <libpipe/rtc/Config.hpp>
#include <libpipe/rtc/ConfigJSON.hpp>


#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {

PipelineLoader::PipelineLoader(const std::map<std::string, std::string>& inputFile)
{
    configuration_ = new ConfigJSON;
    try{
        configuration_->parseInputFile(inputFile);
    } catch (utilities::Exception& e){
        // fix memory leak when the parsing throws an exception.
        delete configuration_;
        throw;
    }
    this->generateFilters();
    this->generatePipeline();
}

PipelineLoader::~PipelineLoader()
{
    delete configuration_;
}

boost::shared_ptr<Filter> PipelineLoader::getFilter(
    const std::string& filtername)
{
    if (filterMap_.find(filtername) != filterMap_.end()) {
        return filterMap_.find(filtername)->second;
    } else {

        std::ostringstream oss;
        oss
                << " LibpipeCreator::getFilter failed, the following filter was not found: "
                << filtername;
        libpipe_fail(oss.str());

    }
}

const Pipeline& PipelineLoader::getPipeline() const
{
    return pipeline_;
}

void PipelineLoader::generateFilters()
{
    std::list<FilterDescription> filterList = configuration_->getFilters();

    for (std::list<FilterDescription>::const_iterator it = filterList.begin();
            it != filterList.end(); ++it) {
        filterMap_[it->filterName] = boost::shared_ptr<Filter>(
            Filter::create(it->filterName, it->algorithmName,
                it->managerName));
    }

    // first all Filters need to be generated before they get connected
    for (FilterMap::const_iterator it = filterMap_.begin();
            it != filterMap_.end(); ++it) {
        this->connectManagers(it->first);
        this->connectAlgorithmPorts(it->first);
    }

}

void PipelineLoader::connectManagers(const std::string& filtername)
{
    std::list<PrecursorDescription> precursors = configuration_->getPrecursorFilter(
        filtername);

    for (std::list<PrecursorDescription>::const_iterator it = precursors.begin();
            it != precursors.end(); ++it) {

        if (filterMap_.find(filtername) != filterMap_.end()) {
            filterMap_.find(filtername)->second->getManager()->connect(
                filterMap_.find(it->precursorName)->second);
        } else {
            libpipe_fail(
                "Something terrible must have occurred, as it should not be possible to call this");
        }

    }

}

void PipelineLoader::connectAlgorithmPorts(const std::string& filtername)
{
    std::list<PortDescription> ports = configuration_->getPort(filtername);

    for (std::list<PortDescription>::const_iterator it = ports.begin();
            it != ports.end(); ++it) {
        if (filterMap_.find(filtername) != filterMap_.end()) {
            filterMap_.find(filtername)->second->getAlgorithm()->connect(
                filterMap_.find(it->filterName)->second->getAlgorithm(),
                it->portNameOfFilter, it->portNameOfThis);
        } else {
            libpipe_fail(
                "Something terrible must have occurred, as it should not be possible to call this");
        }

    }
}

void PipelineLoader::generatePipeline()
{
    std::priority_queue<PipelineDescription, std::vector<PipelineDescription>,
            PipelineDescriptionLess> queue = configuration_->getLibpipePipe();

    while (!queue.empty()) {
        PipelineDescription temp = queue.top();
        queue.pop();

        if (temp.requestType == "UPDATE") {
            Request tempReq(libpipe::Request::UPDATE);
            pipeline_.setTraceFlag(temp.makeTrace);
            pipeline_.push(tempReq, this->getFilter(temp.filterName));
        } else if (temp.requestType == "DELETE") {
            Request tempReq(libpipe::Request::DELETE);
            pipeline_.setTraceFlag(temp.makeTrace);
            pipeline_.push(tempReq, this->getFilter(temp.filterName));
        } else {
            libpipe_fail(
                "Something terrible must have occurred, as it should not be possible to call this");
        }

    }

}

} /* namespace rtc */
} /* namespace libpipe */
