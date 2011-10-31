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
 * \namespace utilities The Namespace where all classes are located which are used for different general usages
 */
namespace utilities {

template<typename IdentifierType, typename ProductType>
class ErrorPolicyThrowException
{
    protected:
        static ProductType* onUnknownType(const IdentifierType& id)
        {
            throw std::bad_typeid();
        }
};

template<typename IdentifierType, typename ProductType>
class ErrorPolicyReturnNull
{
    protected:
        static ProductType* onUnknownType(const IdentifierType& id)
        {
            return 0;
        }
};

template<class AbstractProduct, typename IdentifierType, template<typename,
        class > class FactoryErrorPolicy = ErrorPolicyThrowException,
typename ProductCreatorSignature = AbstractProduct* (*)()>
class Factory : public FactoryErrorPolicy<IdentifierType, AbstractProduct>
{
    public:
        bool registerType(const IdentifierType& id,
            ProductCreatorSignature creator)
        {
            return productMap_.insert(
                typename ProductMap::value_type(id, creator)).second;
        }

        bool unregisterType(const IdentifierType& id)
        {
            return (productMap_.erase(id) == 1);
        }

        AbstractProduct* createObject(const IdentifierType& id) const
        {
            typename ProductMap::const_iterator i = productMap_.find(id);
            if (i != productMap_.end()) {
                return (*i).second();
            }
            return onUnknownType(id);
        }
    public:
        typedef std::map<IdentifierType, ProductCreatorSignature> ProductMap;
        ProductMap productMap_;
};

} //end namespace utilities
} //end namespace libpipe



#endif /* __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_FACTORY_HPP__ */
