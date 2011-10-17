/*
 * LibpipeCreator.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#include <map>
#include <list>
#include <string>

#include "libpipe/rtc/Filter.hpp"
#include "libpipe/rtc/Manager.hpp"
#include "libpipe/rtc/Algorithm.hpp"

#include "libpipe/rtc/LibpipeCreator.hpp"
#include "libpipe/rtc/LibpipeConfig.hpp"
#include "libpipe/rtc/LibpipeConfigLibconfig.hpp"

#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {

LibpipeCreator::LibpipeCreator(std::string const& filepath)
{
    configuration_ = new LibpipeConfigLibconfig(filepath);
    this->generateFilters();
    this->generatePipeline();
}

LibpipeCreator::~LibpipeCreator()
{
    delete configuration_;

}

boost::shared_ptr<Filter> LibpipeCreator::getFilter(
    std::string const& filtername)
{
    if (filterMap_.find(filtername) != filterMap_.end()) {
        return filterMap_.find(filtername)->second;
    } else {
        std::string message =
                " LibpipeCreator::getFilter failed, the following filter was not found: ";
        message += filtername;
        libpipe_fail(message);
    }
}

LibpipePipeline const& LibpipeCreator::getPipeline() const
{
    return pipeline_;
}

void LibpipeCreator::generateFilters()
{
    std::list<FilterStruct> filterList = configuration_->getFilters();

    for (std::list<FilterStruct>::const_iterator it = filterList.begin();
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

void LibpipeCreator::connectManagers(std::string const& filtername)
{
    std::list<PrecursorStruct> precursors = configuration_->getPrecursorFilter(
        filtername);

    for (std::list<PrecursorStruct>::const_iterator it = precursors.begin();
            it != precursors.end(); ++it) {

        if (filterMap_.find(filtername) != filterMap_.end()) {
            filterMap_.find(filtername)->second->getManager()->connect(
                filterMap_.find(it->precursorName)->second);
        } else {
            std::string message =
                    " LibpipeCreator::connectManagers failed, the following filter was not found: ";
            message += filtername;
            libpipe_fail(message);
        }

    }

}

void LibpipeCreator::connectAlgorithmPorts(std::string const& filtername)
{
    std::list<PortStruct> ports = configuration_->getPort(filtername);

    for (std::list<PortStruct>::const_iterator it = ports.begin();
            it != ports.end(); ++it) {
        if (filterMap_.find(filtername) != filterMap_.end()) {
            filterMap_.find(filtername)->second->getAlgorithm()->connect(
                filterMap_.find(it->filterName)->second->getAlgorithm(),
                it->portNameOfFilter, it->portNameOfThis);
        } else {
            std::string message =
                    " LibpipeCreator::connectAlgorithmPorts failed, the following filter was not found: ";
            message += filtername;
            libpipe_fail(message);
        }

    }
}

void LibpipeCreator::generatePipeline()
{
    std::priority_queue<LibpipePipeStruct, std::vector<LibpipePipeStruct>,
            LibpipePipeStructLess> queue = configuration_->getLibpipePipe();

    while (!queue.empty()) {
        LibpipePipeStruct temp = queue.top();
        queue.pop();

        if (temp.requestType == "UPDATE") {
            Request tempReq(libpipe::Request::UPDATE);
            tempReq.setTraceFlag(true);
            pipeline_.push(tempReq, this->getFilter(temp.filterName));
        } else if (temp.requestType == "DELETE") {
            Request tempReq(libpipe::Request::DELETE);
            tempReq.setTraceFlag(true);
            pipeline_.push(tempReq, this->getFilter(temp.filterName));
        } else {
            std::string message =
                    " LibpipeCreator::generatePipeline failed, the following request Type was not found: ";
            message += temp.requestType;
            libpipe_fail(message);
        }

    }

}

} /* namespace rtc */
} /* namespace libpipe */
