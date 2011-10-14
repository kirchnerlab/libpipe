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
#include <sstream>

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

void LibpipeConfigLibconfig::parseInputFile(std::string const& inputFileName)
{

    libconfig::Config cfg;

    // Read the file. If there is an error, report it and exit.
    try {
        cfg.readFile(inputFileName.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        libpipe_fail("I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        std::ostringstream oss;
        oss << "Parse error at " << pex.getFile() << ":"
            << pex.getLine() << " - " << pex.getError();
        libpipe_fail(oss.str());
    }

    const libconfig::Setting& root = cfg.getRoot();

    // Output a list of all books in the inventory.
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

}

} /* namespace rtc */
} /* namespace libpipe */
