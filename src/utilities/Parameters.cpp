/*
 * Parameters.cpp
 *
 *  Copyright (C) 2011 Marc Kirchner
 *
 */
#include <libpipe/utilities/Parameters.hpp>

using namespace libpipe::utilities;

Parameters::InvalidParameterName::InvalidParameterName(const char* message) :
        Exception(message)
{
}

Parameters::InvalidParameterName::InvalidParameterName(const std::string& message) :
        Exception(message)
{
}

Parameters::InvalidParameterName::~InvalidParameterName() throw ()
{
}

Parameters::InvalidParameterType::InvalidParameterType(const char* message) :
        Exception(message)
{
}

Parameters::InvalidParameterType::InvalidParameterType(const std::string& message) :
        Exception(message)
{
}

Parameters::InvalidParameterType::~InvalidParameterType() throw ()
{
}

Parameters::Parameters()
{
}

Parameters::Parameters(const std::vector<std::string>& required,
    const std::vector<std::string>& optional) :
    requiredParams_(required), optionalParams_(optional)
{
}

bool Parameters::count(const std::string& name) const
{
    return params_.count(name);
}

bool Parameters::validate() const
{
    // The set function makes sure that all parameters that are set are
    // valid. Hence, to validate, we only need to check if all required
    // parameters have been set.
    std::vector<std::string>::const_iterator i;
    for (i = requiredParams_.begin(); i != requiredParams_.end(); ++i) {
        if (!params_.count(*i)) {
            return false;
        }
    }
    return true;
}

