/*
 * ObjectFactory-test.cpp
 *
 * Copyright (c) 2011   David Sichau
 *                      Marc Kirchner
 *
 */
#include <libpipe/config.hpp>

#include <iostream>
#include "vigra/unittest.hxx"
#include <libpipe/utilities/Singleton.hpp>
#include <libpipe/utilities/Factory.hpp>

#include <string>
#include <exception>

class AbstractType;

typedef libpipe::utilities::Singleton<
        libpipe::utilities::Factory<AbstractType, std::string> > AbstractFactory;

class AbstractType
{
    public:
        virtual ~AbstractType() = 0;

        virtual std::string getName() = 0;
};

AbstractType::~AbstractType(){}

class ConcreteType : public AbstractType
{
       // virtual ~ConcreteType(){}

        static AbstractType* create(){
            return new ConcreteType;
        }

        virtual std::string getName()
        {
            return "test";
        }

    private:
        static const bool registered_;

        static const bool registerLoader()
        {
            std::string ids="test";
            return AbstractFactory::instance().registerType(ids, ConcreteType::create);
        }
};

const bool ConcreteType::registered_ = registerLoader();

/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct ObjectFactoryTestSuite : vigra::test_suite
{
        /** Constructor.
         * The ObjectFactoryTestSuite constructor adds all ObjectFactory tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        ObjectFactoryTestSuite() :
                vigra::test_suite("utilities/Factory")
        {
            add(testCase(&ObjectFactoryTestSuite::test));
            add(testCase(&ObjectFactoryTestSuite::testWrongType));

        }

        /** Test that is guaranteed to fail.
         * Leave this in until the complete ObjectFactory class has tests.
         */
        void fail()
        {
            failTest("No unit tests for class ObjectFactory!");
        }

        void test()
        {
            std::string ids= "test";
            AbstractType * t = AbstractFactory::instance().createObject(ids);
            shouldEqual(t->getName(), "test");
            delete t;
        }

        void testWrongType(){
            std::string ids="blubb";
            bool thrown=false;
            try{
                AbstractType *t = AbstractFactory::instance().createObject(ids);
                delete t;
            }
            catch(std::exception& e){
                thrown=true;
            }

            shouldEqual(thrown, true);
        }
};

/** The main function that runs the tests for class ObjectFactory.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ObjectFactoryTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

