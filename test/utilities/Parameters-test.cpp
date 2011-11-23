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
#include <libpipe/config.hpp>
#include <libpipe/utilities/Parameters.hpp>

#include <iostream>
#include <boost/assign/std/vector.hpp>

#include "vigra/unittest.hxx"

using namespace libpipe::utilities;
using namespace boost::assign;

struct ParametersTestSuite : vigra::test_suite
{
    ParametersTestSuite() :
        vigra::test_suite("Parameters")
    {
        add(testCase(&ParametersTestSuite::testInstanceBasics));
        add(testCase(&ParametersTestSuite::testSetGet));
        add(testCase(&ParametersTestSuite::testSet));
        add(testCase(&ParametersTestSuite::testGet));
        add(testCase(&ParametersTestSuite::testValidate));
        add(testCase(&ParametersTestSuite::testCount));
    }

    void testInstanceBasics()
    {
        std::vector<std::string> req, opt;
        Parameters p(req, opt);
        Parameters q(p);
        Parameters r = p;
//        shouldEqual(p == q, true);
//        shouldEqual(p == r, true);
//        shouldEqual(q == r, true);
    }

    void testSetGet()
    {
        std::vector<std::string> req, opt;
        req += "p1", "p2", "p3";
        Parameters p(req, opt);
        double p1 = 2.5;
        p.set("p1", p1);
        double q1 = p.get<double> ("p1");
        shouldEqual(p1, q1);
        std::string p2("Hello world!");
        p.set("p2", p2);
        std::string q2 = p.get<std::string> ("p2");
        shouldEqual(p2, q2);
        std::vector<std::string> p3;
        p3 += "lala", "dumdeldei";
        p.set("p3", p3);
        std::vector<std::string> q3 = p.get<std::vector<std::string> > ("p3");
        shouldEqual(p3 == q3, true);
    }

    void testSet()
    {
        std::vector<std::string> req, opt;
        {
            // attempt to add a non-required, non-optional parameter
            Parameters p(req, opt);
            bool thrown = false;
            try {
                p.set("invalid", 4);
            } catch (Parameters::InvalidParameterName& e) {
                thrown = true;
            }
            shouldEqual(thrown, true);
        }
        opt += "valid";
        {
            // attempt to add a non-required, optional parameter
            Parameters p(req, opt);
            bool thrown = false;
            try {
                p.set("valid", 4);
            } catch (Parameters::InvalidParameterName& e) {
                thrown = true;
            }
            shouldEqual(thrown, false);
        }
        opt.clear();
        req += "valid";
        {
            // attempt to add a required parameter
            Parameters p(req, opt);
            bool thrown = false;
            try {
                p.set("valid", 4);
            } catch (Parameters::InvalidParameterName& e) {
                thrown = true;
            }
            shouldEqual(thrown, false);
            // try overwriting
            thrown = false;
            try {
                p.set("valid", "newValueWithDifferentType");
            } catch (Parameters::InvalidParameterName& e) {
                thrown = true;
            }
            shouldEqual(thrown, false);
        }
    }

    void testGet()
    {
        // The normal gets are tested above. Here we only make sure that the
        // expected exceptions are thrown.
        std::vector<std::string> req, opt;
        Parameters p(req, opt);
        bool thrown = false;
        try {
            double x = p.get<double> ("invalid");
        } catch (Parameters::InvalidParameterName& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);
        // Now set up a Parameter object and ask for the wrong type.
        req += "valid";
        Parameters q(req, opt);
        q.set("valid", "some string");
        thrown = false;
        try {
            double x = q.get<double> ("valid");
        } catch (Parameters::InvalidParameterType& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);
    }

    void testValidate()
    {
        std::vector<std::string> req, opt;
        req += "p1", "p2";
        Parameters p(req, opt);
        p.set("p1", -23.5);
        shouldEqual(p.validate(), false);
        p.set("p2", "asdf");
        shouldEqual(p.validate(), true);
    }

    void testCount() {
        std::vector<std::string> req, opt;
        req += "p1", "p2";
        Parameters p(req, opt);
        shouldEqual(p.count("p1"), static_cast<size_t>(0));
        p.set("p1", -23.5);
        shouldEqual(p.count("p1"), static_cast<size_t>(1));
        shouldEqual(p.count("p2"), static_cast<size_t>(0));
        p.set("p2", "asdf");
        shouldEqual(p.count("p2"), static_cast<size_t>(1));
        p.set("p2", "lala");
        shouldEqual(p.count("p2"), static_cast<size_t>(1));
    }
};

int main()
{
    ParametersTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

