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

