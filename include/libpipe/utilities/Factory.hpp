/*
 * Factory.hpp
 *
 *  Copyright (c) 2009 Marc Kirchner
 *                     David Sichau
 *
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