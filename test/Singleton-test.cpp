/*
 * Singleton-test.cpp
 *
 * Copyright (c) 2010 Marc Kirchner <marc.kirchner@childrens.harvard.edu>
 *
 */
#include <utilities/Singleton.hpp>

#include "vigra/unittest.hxx"

class SingletonTest {
  public:
    SingletonTest() : dummy_(0.0) {}
  private:
    double dummy_;
};

struct SingletonTestSuite : vigra::test_suite {
    SingletonTestSuite() : vigra::test_suite("Singleton") {
        add( testCase(&SingletonTestSuite::test));
    }

    void test() {
        typedef Singleton<SingletonTest> ST;
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


