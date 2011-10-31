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

#include <libpipe/utilities/Singleton.hpp>
#include <libpipe/config.hpp>

#include "vigra/unittest.hxx"

class SingletonTest {
  public:
    SingletonTest() : dummy_(0.0) {}
  private:
    double dummy_;
};

struct SingletonTestSuite : vigra::test_suite {
    SingletonTestSuite() : vigra::test_suite("utilities/Singleton") {
        add( testCase(&SingletonTestSuite::test));
    }

    void test() {
        typedef libpipe::utilities::Singleton<SingletonTest> ST;
        SingletonTest& u = ST::instance();
        SingletonTest& v = ST::instance();
        should(&u == &v);
    }

};

int main()
{
    SingletonTestSuite test;
    int failed = test.run();
    std::cout << test.report() << std::endl;
    return failed;
}


