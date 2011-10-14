/*
 * LibpipeConfigLibconfig.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 */

#include "libpipe/rtc/LibpipeConfigLibconfig.hpp"
#include <libpipe/Exception.hpp>

#include <libconfig.h++>
#include <string>

namespace libpipe {
namespace rtc {

LibpipeConfigLibconfig::LibpipeConfigLibconfig(std::string const& fileName)
{
    this->parseInputFile(fileName);

}

LibpipeConfigLibconfig::~LibpipeConfigLibconfig()
{
    // TODO Auto-generated destructor stub
}

std::list<FilterStruct> const& LibpipeConfigLibconfig::getFilters() const
{
    return filterList_;
}

std::list<PrecursorStruct> const& LibpipeConfigLibconfig::getPrecursorFilter(
    std::string const& filtername) const
{
    for (std::list<FilterStruct>::const_iterator it = filterList_.begin();
            it != filterList_.end(); ++it) {
        if (it->filterName == filtername) {
            return it->precursors;
        }
    }
    std::string message =
            "LibpipeConfigLibconfig::getPrecursorFilter failed, the following filter was not registered: ";
    message += filtername;
    libpipe_fail(message);
}

std::list<PortStruct> const& LibpipeConfigLibconfig::getPort(
    std::string const& filtername) const
{
    for (std::list<FilterStruct>::const_iterator it = filterList_.begin();
            it != filterList_.end(); ++it) {
        if (it->filterName == filtername) {
            return it->ports;
        }
    }
    std::string message =
            "LibpipeConfigLibconfig::getPort failed, the following filter was not registered: ";
    message += filtername;
    libpipe_fail(message);
}

std::priority_queue<LibpipePipeStruct, std::vector<LibpipePipeStruct>,
        LibpipePipeStructLess> const& LibpipeConfigLibconfig::getLibpipePipe() const
{
    return requestQueue_;
}

void LibpipeConfigLibconfig::parseInputFile(std::string const& inputFileName)
{

    libconfig::Config cfg;

    // Read the file. If there is an error, report it and exit.
    try {
        cfg.readFile(inputFileName.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        libpipe_fail("I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        std::string message = "Parse error at ";
        message += pex.getFile();
        message += ":";
        message += pex.getLine();
        message += " - ";
        message += pex.getError();
        libpipe_fail(message);
    }

    const libconfig::Setting& root = cfg.getRoot();

    // generates the filters
    try {
        const libconfig::Setting &filters = root["filters"];

        for (int i = 0; i < filters.getLength(); ++i) {
            const libconfig::Setting &filter = filters[i];

            // Only output the record if all of the expected fields are present.
            std::string filterName, algorithmName, managerName;

            if (!(filter.lookupValue("filterName", filterName)
                    && filter.lookupValue("algorithmName", algorithmName)
                    && filter.lookupValue("managerName", managerName)))
                continue;

            FilterStruct tempFilterStruct;
            tempFilterStruct.filterName = filterName;
            tempFilterStruct.algorithmName = algorithmName;
            tempFilterStruct.managerName = managerName;

            // get precursors
            const libconfig::Setting &precursors = filter["precursors"];
            PrecursorStruct tempPrecursor;
            for (int j = 0; j < precursors.getLength(); ++j) {
                const libconfig::Setting &precursor = precursors[j];
                std::string precursorName;
                if (!(precursor.lookupValue("precursorName", precursorName)))
                    continue;

                tempPrecursor.precursorName = precursorName;
                tempFilterStruct.precursors.push_back(tempPrecursor);
            }

            //get ports
            const libconfig::Setting &ports = filter["ports"];
            PortStruct tempPorts;
            for (int k = 0; k < ports.getLength(); ++k) {
                const libconfig::Setting &port = ports[k];
                std::string filterName, portNameOfFilter, portNameOfThis;
                if (!(port.lookupValue("filterName", filterName)
                        && port.lookupValue("portNameOfFilter",
                            portNameOfFilter)
                        && port.lookupValue("portNameOfThis", portNameOfThis)))
                    continue;

                tempPorts.filterName = filterName;
                tempPorts.portNameOfFilter = portNameOfFilter;
                tempPorts.portNameOfThis = portNameOfThis;
                tempFilterStruct.ports.push_back(tempPorts);

            }
            filterList_.push_back(tempFilterStruct);
        }

    } catch (const libconfig::SettingNotFoundException &nfex) {
        // Ignore.
    }

    // generates the requests
    try {
        const libconfig::Setting &requests = root["request"];

        for (int i = 0; i < requests.getLength(); ++i) {
            const libconfig::Setting &request = requests[i];
            LibpipePipeStruct tempLibpipeRequest;

            // Only output the record if all of the expected fields are present.
            std::string filterName;
            unsigned int requestRank;
            int requestType;

            if (!(request.lookupValue("filteName", filterName)
                    && request.lookupValue("requestType", requestType)
                    && request.lookupValue("requestRank", requestType)))
                continue;

            tempLibpipeRequest.filterName = filterName;
            tempLibpipeRequest.requestType = requestType;
            tempLibpipeRequest.requestType = requestType;

            requestQueue_.push(tempLibpipeRequest);
        }

    } catch (const libconfig::SettingNotFoundException &nfex) {
        // Ignore.
    }
}

} /* namespace rtc */
} /* namespace libpipe */
