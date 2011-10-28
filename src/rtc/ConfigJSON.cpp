/*
 * LibpipeConfigLibconfig.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */
#include <libpipe/config.hpp>

#include <libpipe/rtc/ConfigJSON.hpp>
#include <libpipe/utilities/Exception.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <string>
#include <map>
#include <sstream>

namespace libpipe {
namespace rtc {

ConfigJSON::ConfigJSON()
{
}

ConfigJSON::~ConfigJSON()
{

}

const std::list<FilterDescription>& ConfigJSON::getFilters() const
{
    return filterList_;
}

const std::list<PrecursorDescription>& ConfigJSON::getPrecursorFilter(
    const std::string& filtername) const
{
    for (std::list<FilterDescription>::const_iterator it = filterList_.begin();
            it != filterList_.end(); ++it) {
        if (it->filterName == filtername) {
            return it->precursors;
        }
    }

    std::ostringstream oss;
    oss
            << "LibpipeConfigLibconfig::getPrecursorFilter failed, the following filter was not registered: "
            << filtername;
    libpipe_fail(oss.str());

}

const std::list<PortDescription>& ConfigJSON::getPort(
    const std::string& filtername) const
{
    for (std::list<FilterDescription>::const_iterator it = filterList_.begin();
            it != filterList_.end(); ++it) {
        if (it->filterName == filtername) {
            return it->ports;
        }
    }

    std::ostringstream oss;
    oss
            << "LibpipeConfigLibconfig::getPort failed, the following filter was not registered: "
            << filtername;
    libpipe_fail(oss.str());
}

std::priority_queue<PipelineDescription, std::vector<PipelineDescription>,
        PipelineDescriptionLess> ConfigJSON::getLibpipePipe() const
{
    return requestQueue_;
}

void ConfigJSON::parseInputFile(const std::map<std::string, std::string>& filename)
{

    boost::property_tree::ptree ptFilter;
    boost::property_tree::ptree ptConnections;
    boost::property_tree::ptree ptPipeline;

    // Read the file. If there is an error, report it and exit.
    try {
        boost::property_tree::read_json(filename.find("FilterInput")->second, ptFilter);
    } catch (std::exception& e) {
        std::ostringstream oss;
        oss << "I/O error while reading Filter file. With exception: "
                << e.what();
        libpipe_fail(oss.str());
    }

    std::map<std::string, std::string> algorithmMap;
    std::map<std::string, std::string> managerMap;

    BOOST_FOREACH(boost::property_tree::ptree::value_type & v,
            ptFilter.get_child("filters"))
            {
                algorithmMap[v.second.get<std::string>("filterIdentifier")] =
                        v.second.get<std::string>("algorithmName");
                managerMap[v.second.get<std::string>("filterIdentifier")] =
                        v.second.get<std::string>("managerName");

            }
// Read the file. If there is an error, report it and exit.
    try {
        boost::property_tree::read_json(filename.find("ConnectionInput")->second,
            ptConnections);
    } catch (std::exception& e) {
        std::ostringstream oss;
        oss << "I/O error while reading Connection file. With exception: "
                << e.what();
        libpipe_fail(oss.str());
    }

    BOOST_FOREACH(boost::property_tree::ptree::value_type & v,
            ptConnections.get_child("connections"))
            {

                FilterDescription tempFilterStruct;

                tempFilterStruct.filterName = v.second.get<std::string>(
                    "filterName");
                tempFilterStruct.algorithmName = algorithmMap[v.second.get<
                        std::string>("identifier")];
                tempFilterStruct.managerName = managerMap[v.second.get<
                        std::string>("identifier")];

                PrecursorDescription tempPrecursor;
                BOOST_FOREACH(boost::property_tree::ptree::value_type & t,
                        v.second.get_child("precursors"))
                        {
                            tempPrecursor.precursorName = t.second.get<
                                    std::string>("precursorName");
                            tempFilterStruct.precursors.push_back(
                                tempPrecursor);
                        }

                PortDescription tempPorts;
                BOOST_FOREACH(boost::property_tree::ptree::value_type & t,
                        v.second.get_child("ports"))
                        {
                            tempPorts.filterName = t.second.get<std::string>(
                                "filterName");
                            tempPorts.portNameOfFilter = t.second.get<
                                    std::string>("portNameOfFilter");
                            tempPorts.portNameOfThis =
                                    t.second.get<std::string>(
                                        "portNameOfThis");
                            tempFilterStruct.ports.push_back(tempPorts);
                        }
                filterList_.push_back(tempFilterStruct);
            }
    // generates the pipeline
    // Read the file. If there is an error, report it and exit.
    try {
        boost::property_tree::read_json(filename.find("PipelineInput")->second,
            ptPipeline);
    } catch (std::exception& e) {
        std::ostringstream oss;
        oss << "I/O error while reading Pipeline file. With exception: "
                << e.what();
        libpipe_fail(oss.str());
    }

    BOOST_FOREACH(boost::property_tree::ptree::value_type & v,
            ptPipeline.get_child("pipeline"))
            {
                PipelineDescription tempLibpipeRequest;

                tempLibpipeRequest.filterName = v.second.get<std::string>(
                    "filterName");
                tempLibpipeRequest.requestRank = v.second.get<int>(
                    "requestRank");
                tempLibpipeRequest.requestType = v.second.get<std::string>(
                    "requestType");
                tempLibpipeRequest.makeTrace = v.second.get<bool>("makeTrace",
                    false);

                requestQueue_.push(tempLibpipeRequest);
            }

}

bool ConfigJSON::checkFile(const std::map<std::string, std::string>& filename) const
{
    return true;
    ///TODO implement test
}

} /* namespace rtc */
} /* namespace libpipe */
