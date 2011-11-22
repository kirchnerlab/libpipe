/*
 *
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
 * \namespace libpipe::utilities The Namespace where all classes are located which are used for different general usages
 */
namespace utilities {

/**
 * Throws an exception at errors
 */
template<typename IdentifierType, typename ProductType>
class ErrorPolicyThrowException
{
    protected:
        /** error policy for unknown type
         * @param id The identifier of the unknown type
         * @return throws an exception
         */
        static ProductType* onUnknownType(const IdentifierType& id)
        {
            throw std::bad_typeid();
        }
};

/**
 * Returns a 0 pointer at errors
 */
template<typename IdentifierType, typename ProductType>
class ErrorPolicyReturnNull
{
    protected:
        /** error policy for unknown type
         * @param id The identifier of the unknown type
         * @return a 0 pointer
         */
        static ProductType* onUnknownType(const IdentifierType& id)
        {
            return 0;
        }
};

/** Implementation of an factory to register generation of objects.
 *
 */
template<class AbstractProduct, typename IdentifierType, template<typename,
        class > class FactoryErrorPolicy = ErrorPolicyThrowException,
typename ProductCreatorSignature = AbstractProduct* (*)()>
class LIBPIPE_EXPORT Factory : public FactoryErrorPolicy<IdentifierType,
        AbstractProduct>
{
    public:
        /** Registers a class
         * @param id The identifier of the class
         * @param creator the creator method of the class
         * @return true if successful
         */
        bool registerType(const IdentifierType& id,
            ProductCreatorSignature creator)
        {
            return productMap_.insert(
                typename ProductMap::value_type(id, creator)).second;
        }

        /** unregisters a class
         * @param id The identifier of the class
         * @return true if successful
         */
        bool unregisterType(const IdentifierType& id)
        {
            return (productMap_.erase(id) == 1);
        }

        /** creates an instance of the class
         * @param id the identifier of the class
         * @return a pointer to an new instance of the class
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
        /** typedef of the map used to store the creator methods
         */
        typedef std::map<IdentifierType, ProductCreatorSignature> ProductMap;
        /** the actual map where the creator methods are stored.
         */
        ProductMap productMap_;
};

} //end namespace utilities
} //end namespace libpipe

#endif /* __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_FACTORY_HPP__ */
