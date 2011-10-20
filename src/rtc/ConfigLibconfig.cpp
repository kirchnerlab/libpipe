/*
 * LibpipeConfigLibconfig.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */
#include <libpipe/config.hpp>

#include <libpipe/rtc/ConfigLibconfig.hpp>
#include <libpipe/Exception.hpp>

#include <libconfig.h++>

#include <string>
#include <map>
#include <sstream>

namespace libpipe {
namespace rtc {

ConfigLibconfig::ConfigLibconfig()
{
}

ConfigLibconfig::~ConfigLibconfig()
{

}

std::list<FilterDescription> const& ConfigLibconfig::getFilters() const
{
    return filterList_;
}

std::list<PrecursorDescription> const& ConfigLibconfig::getPrecursorFilter(
    std::string const& filtername) const
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

std::list<PortDescription> const& ConfigLibconfig::getPort(
    std::string const& filtername) const
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
        PipelineDescriptionLess> ConfigLibconfig::getLibpipePipe() const
{
    return requestQueue_;
}

void ConfigLibconfig::parseInputFile(std::string const& inputFileName)
{

    libconfig::Config cfg;

    // Read the file. If there is an error, report it and exit.
    try {
        cfg.readFile(inputFileName.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        libpipe_fail("I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        std::ostringstream oss;
        oss << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError();
        libpipe_fail(oss.str());
    }

    const libconfig::Setting& root = cfg.getRoot();

    std::map<std::string, std::string> algorithmMap;
    std::map<std::string, std::string> managerMap;

    try {
        const libconfig::Setting &filters = root["filters"];
        for (int i = 0; i < filters.getLength(); ++i) {
            const libconfig::Setting &filter = filters[i];
            std::string filterIdentifier, algorithmName, managerName;

            if (!(filter.lookupValue("filterIdentifier", filterIdentifier)
                    && filter.lookupValue("algorithmName", algorithmName)
                    && filter.lookupValue("managerName", managerName))) {
                continue;
            }
            algorithmMap[filterIdentifier] = algorithmName;
            managerMap[filterIdentifier] = managerName;
        }

        const libconfig::Setting &connections = root["connections"];

        for (int i = 0; i < connections.getLength(); ++i) {
            const libconfig::Setting &filter = connections[i];

            // Only output the record if all of the expected fields are present.
            std::string filterName, identifier;

            if (!(filter.lookupValue("filterName", filterName)
                    && filter.lookupValue("identifier", identifier))) {
                continue;
            }

            FilterDescription tempFilterStruct;
            tempFilterStruct.filterName = filterName;
            tempFilterStruct.algorithmName = algorithmMap[identifier];
            tempFilterStruct.managerName = managerMap[identifier];

            // get precursors
            const libconfig::Setting &precursors = filter["precursors"];
            PrecursorDescription tempPrecursor;
            for (int j = 0; j < precursors.getLength(); ++j) {
                const libconfig::Setting &precursor = precursors[j];
                std::string precursorName;
                if (!(precursor.lookupValue("precursorName", precursorName))) {
                    continue;
                }

                tempPrecursor.precursorName = precursorName;
                tempFilterStruct.precursors.push_back(tempPrecursor);
            }

            //get ports
            const libconfig::Setting &ports = filter["ports"];
            PortDescription tempPorts;
            for (int k = 0; k < ports.getLength(); ++k) {
                const libconfig::Setting &port = ports[k];
                std::string filterName, portNameOfFilter, portNameOfThis;
                if (!(port.lookupValue("filterName", filterName)
                        && port.lookupValue("portNameOfFilter",
                            portNameOfFilter)
                        && port.lookupValue("portNameOfThis", portNameOfThis))) {
                    continue;
                }

                tempPorts.filterName = filterName;
                tempPorts.portNameOfFilter = portNameOfFilter;
                tempPorts.portNameOfThis = portNameOfThis;
                tempFilterStruct.ports.push_back(tempPorts);

            }
            filterList_.push_back(tempFilterStruct);
        }

        // generates the requests

        const libconfig::Setting &requests = root["request"];

        for (int i = 0; i < requests.getLength(); ++i) {
            const libconfig::Setting &request = requests[i];
            PipelineDescription tempLibpipeRequest;

            // Only output the record if all of the expected fields are present.
            std::string filterName, requestType;
            unsigned int requestRank;
            bool trace = false;

            if (!(request.lookupValue("filterName", filterName)
                    && request.lookupValue("requestType", requestType)
                    && request.lookupValue("requestRank", requestRank)
                    && request.lookupValue("makeTrace", trace))) {
                continue;
            }
            tempLibpipeRequest.filterName = filterName;
            tempLibpipeRequest.requestRank = requestRank;
            tempLibpipeRequest.requestType = requestType;
            tempLibpipeRequest.makeTrace = trace;

            requestQueue_.push(tempLibpipeRequest);
        }

    } catch (const libconfig::SettingNotFoundException &nfex) {
        libpipe_fail("Problems with settings in the input file.");
    }
}

bool ConfigLibconfig::checkFile() const
{
    return true;
    ///TODO implement test
}

} /* namespace rtc */
} /* namespace libpipe */
