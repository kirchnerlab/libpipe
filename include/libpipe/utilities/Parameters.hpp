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

#ifndef __LIBPIPE_INCLUDE_UTILITIES_PARAMETERS_HPP__
#define __LIBPIPE_INCLUDE_UTILITIES_PARAMETERS_HPP__

#include <libpipe/config.hpp>
#include <libpipe/utilities/Exception.hpp>
#include <string>
#include <vector>
#include <map>
#include <vector>
#include <boost/variant.hpp>
namespace libpipe {
namespace utilities {

/** Generic parameter collection class.
 * The Parameters class is a (somewhat) generic collection of key/value
 * pairs intended for use as a parameter object. The implementation is
 * based on an underlying variant that can take any type but has currently
 * been limited to
 * \code
 *      size_t, int, double, std::string, std::vector<size_t>, std::vector<int>,
 std::vector<double>, std::vector<std::string> >, std::pair<double, double>
 * \endcode
 * Using \c Parameters instances is straightforward, however there are a few
 * best practices:
 * \li in most cases a \c Parameters instance will be part of e.g. a \c Filter
 *     or an algorithm class/object. In this case, the containing class should
 *     provide \c get functionality to a properly instanciated \c Parameters
 *     object, that has been initialized with the correct required and optional
 *     parameter names (i.e. keys) as well as \c set functionality for the
 *     complete \c Parameters instance.
 * \code
 *     // SomeObject constructor:
 *     SomeObject::SomeObject(...) : ...
 *     {
 *         ...
 *         std::vector<std::string> req, opt;
 *         req.push_back("delta");
 *         opt.push_back("solution");
 *         params_ = Parameters(req, opt);
 *         ...
 *     }
 * \endcode
 * \li in such cases, the client code should not attempt to construct a
 *     parameter object from scratch but instead copy the existing object:
 * \code
 *    Parameters p = someObject.getParameters();
 *    p.set("delta", 0.773);
 *    p.set("solution", 42);
 *    someObject.setParameters(p);
 * \endcode
 * \li before using the values in a \c Parameters object, the callee should
 *     validate the contents to see if the required keys are present:
 * \code
 *     ...
 *     bool isGood = p.validate();
 *     ...
 *     if (!isGood) {
 *         throw UnleashMayhem("Oops.");
 *     }
 *     ...
 * \endcode
 *
 * See the tests for more examples.
 */
class Parameters
{
    public:
        /** Exception class instances of which are thrown if a requested
         *  parameter key is invalid.
         */
        class InvalidParameterName : public Exception
        {
            public:
                explicit InvalidParameterName(const char* message);
                explicit InvalidParameterName(const std::string& message);
                virtual ~InvalidParameterName() throw ();
        };

        /** Exception class; signifies runtime type errors while using the
         *  \c Parameter interface.
         */
        class InvalidParameterType : public Exception
        {
            public:
                explicit InvalidParameterType(const char* message);
                explicit InvalidParameterType(const std::string& message);
                virtual ~InvalidParameterType() throw ();
        };

        explicit Parameters();

        /** Constructor.
         * @param[in] required The names (keys) of required parameters. These keys
         *                     will be required for validate() to succeed.
         * @param[in] optional The names (keys) of required parameters.
         */
        Parameters(const std::vector<std::string>& required,
            const std::vector<std::string>& optional);

        /** Adds a new required Parameter to the Parameters
         * @param required The name (key) of a additional required parameter
         */
        void addRequiredParameters(const std::string& required);
        /** Adds a new optinal Parameter to the Parameters
         * @param optional The name (key) of a additional optional parameter
         */
        void addOptionalParameters(const std::string& optional);

        /** Set a key/value pair.
         * @param key The key.
         * @param value The value.
         * @throw Throws \c InvalidParameterName if the key is not among the
         *        required or optional keys.
         */
        template<typename T>
        void set(const std::string& key, const T& value);

        /** Retrieve the value for a specific key.
         * Type conversion is implemented using the template parameter:
         * \code
         *     ...
         *     Parameters p(req, opt);
         *     p.set("name", "someValue");
         *     std::string s = p.get<std::string>("name");
         *     ...
         * \endcode
         * @param key The key of interest.
         * @return A const reference to the value associated with the key \c key.
         * @throw Throws \c InvalidParameterName if the key is not among the
         *        required or optional keys and \c InvalidParameterType if the
         *        requested type does not match the stored type.
         */
        template<typename T>
        const T& get(const std::string& key);

        /** Check if a particular parameter name (i.e. key) exists.
         *
         * @param key The key for which the check is requested.
         * @return True if the key is found. Always false for invalid parameters.
         */
        bool count(const std::string& key) const;

        /** Check if all required parameters have been set.
         * This check if all required key have be associated with a value. Note that
         * this does NOT check if the types of the values are correct (as the
         * expected type is currently not stored).
         * @return True if all required parameters are associated with a value.
         */
        bool validate() const;

        typedef boost::variant<size_t, int, double, std::string,
                std::vector<size_t>, std::vector<int>, std::vector<double>,
                std::vector<std::string>, std::pair<double, double> > Variant;

    private:
        std::vector<std::string> requiredParams_, optionalParams_;

        typedef std::map<std::string, Variant> Map;
        Map params_;
};

}
}

//
// template implementations
//

namespace libpipe {
namespace utilities {

template<typename T>
void Parameters::set(const std::string& key, const T& value)
{
    // check if the parameter is known
    std::vector<std::string>::const_iterator iRequired;
    iRequired = find(requiredParams_.begin(), requiredParams_.end(), key);
    if (iRequired == requiredParams_.end()) {
        std::vector<std::string>::const_iterator iOptional;
        iOptional = find(optionalParams_.begin(), optionalParams_.end(), key);
        if (iOptional == optionalParams_.end()) {
            throw InvalidParameterName("Invalid parameter key: " + key);
        }
    }
    params_[key] = value;
}

template<typename T>
const T& Parameters::get(const std::string& key)
{
    Map::iterator i = params_.find(key);
    if (i == params_.end()) {
        throw InvalidParameterName("Parameter does not exist: " + key);
    }
    try {
        return boost::get<T>(i->second);
    } catch (boost::bad_get&) {
        throw InvalidParameterType(
            "Request for parameter " + key + " expects wrong type.");
    }
}

}
}

#endif /* __LIBPIPE_INCLUDE_UTILITIES_PARAMETERS_HPP__ */
