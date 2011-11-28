/*
 *
 * Copyright (c) 2011 Marc Kirchner
 * Copyright (c) 2011 David-Matthias Sichau
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
#include <libpipe/utilities/Parameters.hpp>

using namespace libpipe::utilities;

Parameters::InvalidParameterName::InvalidParameterName(const char* message) :
        Exception(message)
{
}

Parameters::InvalidParameterName::InvalidParameterName(
    const std::string& message) :
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

Parameters::InvalidParameterType::InvalidParameterType(
    const std::string& message) :
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

void Parameters::addRequiredParameters(const std::string& required)
{
    requiredParams_.push_back(required);
}

void Parameters::addOptionalParameters(const std::string& optional)
{
    optionalParams_.push_back(optional);
}

