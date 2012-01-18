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
#include <boost/lexical_cast.hpp>

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
 *     provide \c get functionality to a properly instantiated \c Parameters
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
 * \li before using the values in a \c Parameters object, the client should
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
    /** Exception class for invalid parameter keys.
     */
    class InvalidParameterName : public Exception
    {
    public:
        /** Exception Constructor from C string
         * @param message
         */
        explicit InvalidParameterName(const char* message);

        /** Exception Constructor from std::string
         * @param message
         */
        explicit InvalidParameterName(const std::string& message);

        /** virtual Destructor
         */
        virtual ~InvalidParameterName() throw ();
    };

    /** Exception class for runtime type errors while using the
     *  \c Parameter interface.
     */
    class InvalidParameterType : public Exception
    {
    public:
        /** Exception Constructor from C string
         * @param message
         */
        explicit InvalidParameterType(const char* message);

        /** Exception Constructor from std::string
         * @param message
         */
        explicit InvalidParameterType(const std::string& message);

        /** virtual Destructor
         */
        virtual ~InvalidParameterType() throw ();
    };

    /** Explicit constructor to avoid implicit type conversions.
     */
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
     * Type conversion is implemented using the template parameter with boost::lexical_cast:
     * \code
     *     ...
     *     Parameters p(req, opt);
     *     p.set("name", "someValue");
     *     std::string s = p.get<std::string>("name");
     *     ...
     * \endcode
     * @param key The key of interest.
     * @return A copy to the value associated with the key \c key.
     * @throw Throws \c InvalidParameterName if the key is not among the
     *        required or optional keys and \c InvalidParameterType if the
     *        requested type does not match the stored type.
     */
    template<typename T>
    const T get(const std::string& key);

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

private:
    /** Possible types that can be stored by Parameters
     */
    typedef boost::variant<std::string, std::vector<std::string> > Variant;

    /** Storage of required Parameters
     */
    std::vector<std::string> requiredParams_;
    /** Storage of optional Parameters
     */
    std::vector<std::string> optionalParams_;

    /** Typedef of Parameters Map
     */
    typedef std::map<std::string, Variant> Map;
    /** Store the actual parameters
     */
    Map params_;

    /** Internal retrieve the value for a specific key.
     * Type conversion is implemented using the template parameter:
     * @param key The key of interest.
     * @return A copy to the value associated with the key \c key.
     * @throw Throws \c InvalidParameterName if the key is not among the
     *        required or optional keys and \c InvalidParameterType if the
     *        requested type does not match the stored type.
     */
    template<typename T>
    const T get_impl(const std::string& key, T*);

    /** Internal retrieve the value for a specific key.
     * Type conversion is implemented using the template parameter:    ...
     * @param key The key of interest.
     * @return A copy to the value associated with the key \c key.
     * @throw Throws \c InvalidParameterName if the key is not among the
     *        required or optional keys and \c InvalidParameterType if the
     *        requested type does not match the stored type.
     */
    template<typename T>
    const std::vector<T> get_impl(const std::string& key, std::vector<T> *);

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
const T Parameters::get(const std::string& key)
{

    //The static_cast<T*>(0) in get is just a tricky way to disambiguate the call.
    //The type of static_cast<T*>(0) is T*, and passing it as second argument to
    //get_impl will help compiler to choose the correct version of get_impl.
    //If T is not std::vector, the first version will be chosen, otherwise the second
    //version will be chosen.
    return get_impl(key, static_cast<T*> (0));
}

//general case
template<typename T>
const T Parameters::get_impl(const std::string& key, T*)
{

    Map::iterator i = params_.find(key);
    if (i == params_.end()) {
        throw InvalidParameterName("Parameter does not exist: " + key);
    }
    try {
        return boost::lexical_cast<T>(boost::get<std::string>(i->second));
    } catch (boost::bad_lexical_cast&) {
        throw InvalidParameterType(
            "Request for parameter " + key + " wrong conversation.");
    } catch (boost::bad_get&) {
        throw InvalidParameterType(
            "Request for parameter " + key + " expects wrong type.");
    }
}

//template overload
template<typename T>
const std::vector<T> Parameters::get_impl(const std::string& key,
    std::vector<T> *)
{
    Map::iterator i = params_.find(key);
    if (i == params_.end()) {
        throw InvalidParameterName("Parameter does not exist: " + key);
    }
    try {
        std::vector < std::string > temp
                = boost::get<std::vector<std::string> >(i->second);
        std::vector<T> ret;
        for (std::vector<std::string>::const_iterator it = temp.begin(); it
                != temp.end(); it++) {
            ret.push_back(boost::lexical_cast<T>(*it));
        }
        return ret;
    } catch (boost::bad_lexical_cast&) {
        throw InvalidParameterType(
            "Request for parameter " + key + " wrong conversation.");
    } catch (boost::bad_get&) {
        throw InvalidParameterType(
            "Request for parameter " + key + " expects wrong type.");
    }
}

}
}

#endif /* __LIBPIPE_INCLUDE_UTILITIES_PARAMETERS_HPP__ */
