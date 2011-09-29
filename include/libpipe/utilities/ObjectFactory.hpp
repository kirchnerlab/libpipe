/*
 * ObjectFactory.hpp
 *
 *  Copyright (c) 2009 Marc Kirchner <marc.kirchner@iwr.uni-heidelberg.de>
 *  Created on: 29.09.2011
 *      Author: david
 */

#ifndef OBJECTFACTORY_HPP_
#define OBJECTFACTORY_HPP_

#include <map>
#include <exception>
#include <typeinfo>
#include <iostream>

namespace test {

namespace FactorySite {

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
    private:
        typedef std::map<IdentifierType, ProductCreatorSignature> ProductMap;
        ProductMap productMap_;
};

}

}

#endif /* OBJECTFACTORY_HPP_ */
