/*
 * LibpipeCreator.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */
#include <libpipe/config.hpp>

#include <map>
#include <list>
#include <string>
#include <sstream>

#include <libpipe/rtc/Filter.hpp>
#include <libpipe/rtc/Manager.hpp>
#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Controler.hpp>
#include <libpipe/rtc/Config.hpp>
#include <libpipe/rtc/ConfigJSON.hpp>


#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {

Controler::Controler(const std::map<std::string, std::string>& inputFile)
{
    configuration_ = new ConfigJSON;
    try{
        configuration_->parseInputFile(inputFile);
    } catch (utilities::Exception& e){
        // fix memory leak when the parsing throws an exception.
        delete configuration_;
        throw e;
    }
    this->generateFilters();
    this->generatePipeline();
}

Controler::~Controler()
{
    delete configuration_;
}

boost::shared_ptr<Filter> Controler::getFilter(
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

const Pipeline& Controler::getPipeline() const
{
    return pipeline_;
}

void Controler::generateFilters()
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

void Controler::connectManagers(const std::string& filtername)
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

void Controler::connectAlgorithmPorts(const std::string& filtername)
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

void Controler::generatePipeline()
{
    std::priority_queue<PipelineDescription, std::vector<PipelineDescription>,
            PipelineDescriptionLess> queue = configuration_->getLibpipePipe();

    while (!queue.empty()) {
        PipelineDescription temp = queue.top();
        queue.pop();

        if (temp.requestType == "UPDATE") {
            Request tempReq(libpipe::Request::UPDATE);
            tempReq.setTraceFlag(temp.makeTrace);
            pipeline_.push(tempReq, this->getFilter(temp.filterName));
        } else if (temp.requestType == "DELETE") {
            Request tempReq(libpipe::Request::DELETE);
            tempReq.setTraceFlag(temp.makeTrace);
            pipeline_.push(tempReq, this->getFilter(temp.filterName));
        } else {
            libpipe_fail(
                "Something terrible must have occurred, as it should not be possible to call this");
        }

    }

}

} /* namespace rtc */
} /* namespace libpipe */
