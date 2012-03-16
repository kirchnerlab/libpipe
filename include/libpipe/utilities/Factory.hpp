/*
 * Copyright (c) 2011 David-Matthias Sichau
 * Copyright (c) 2010 Marc Kirchner
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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_FACTORY_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_FACTORY_HPP__

#include <libpipe/config.hpp>

#include <map>
#include <exception>
#include <typeinfo>

namespace libpipe {
/**
 * \namespace libpipe::utilities Libpipe utility classes namespace.
 */
namespace utilities {

/**
 * Error policy that throws an exception.
 */
template<typename IdentifierType, typename ProductType>
class ErrorPolicyThrowException
{
protected:
    /** Throw an exception of an unknown type is encountered.
     * @param id The identifier of the unknown type
     * @return throws an exception
     */
    static ProductType* onUnknownType(const IdentifierType& id)
    {
        throw std::bad_typeid();
    }
};

/**
 * Error policy that returns a null pointer.
 */
template<typename IdentifierType, typename ProductType>
class ErrorPolicyReturnNull
{
protected:
    /** Return a numm pointer.
     * @param id The identifier of the unknown type
     * @return a 0 pointer
     */
    static ProductType* onUnknownType(const IdentifierType& id)
    {
        return 0;
    }
};

/** Factory implementation, following [Alexandescu, 2002].
 */
template<
class AbstractProduct,
typename IdentifierType,
template<typename,class > class FactoryErrorPolicy = ErrorPolicyThrowException,
typename ProductCreatorSignature = AbstractProduct* (*)()
> class LIBPIPE_EXPORT Factory : public FactoryErrorPolicy<
    IdentifierType,
    AbstractProduct
>
{
public:
    /** Registers a type with the factory.
     * @param id The identifier of the type.
     * @param creator Function pointer to the type creation method.
     * @return A boolean, true on success.
     */
    bool registerType(const IdentifierType& id,
            ProductCreatorSignature creator)
    {
        return productMap_.insert(
                typename ProductMap::value_type(id, creator)).second;
    }

    /** Unregisters a type.
     * @param id The type identifier.
     * @return A boolean, true on success.
     */
    bool unregisterType(const IdentifierType& id)
    {
        return (productMap_.erase(id) == 1);
    }

    /** Create an instance of the specified type.
     * @param id The type identifier.
     * @return A pointer to an new instance of the requested type.
     * @note The behavior upon requesting a non-existent type id
     *       defined by the FactoryErrorPolicy policy.
     */
    AbstractProduct* createObject(const IdentifierType& id) const
    {
        typename ProductMap::const_iterator i = productMap_.find(id);
        if (i != productMap_.end()) {
            return (*i).second();
        }
        return onUnknownType(id);
    }
public:
    /** Define a type that maps between type ids
     * and the pointers to their creation methods.
     */
    typedef std::map<IdentifierType, ProductCreatorSignature> ProductMap;

    /** The mapping between type ids and function pointers.
     */
    ProductMap productMap_;
};

} //end namespace utilities
} //end namespace libpipe

#endif /* __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_FACTORY_HPP__ */
