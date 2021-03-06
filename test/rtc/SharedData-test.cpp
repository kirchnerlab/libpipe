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
#ifndef  _WIN32
    #define private public
    #define protected public
#endif
#include <libpipe/rtc/SharedData.hpp>
#ifndef  _WIN32
    #undef private
    #undef protected
#endif


using namespace libpipe::rtc;

/** Test suite for the SharedData template class
 */
struct SharedDataTestSuite : vigra::test_suite
{
        /** Constructor.
         * The SharedDataTestSuite constructor adds all SharedData tests to
         * the test suite. If you write an additional test, add the test
         * case here.
         */
        SharedDataTestSuite() :
                vigra::test_suite("rtc/SharedData")
        {
#ifdef ENABLE_THREADING
            add(testCase(&SharedDataTestSuite::instanceThreading));
#ifndef _WIN32
            add(testCase(&SharedDataTestSuite::locking));
#endif
            add(testCase(&SharedDataTestSuite::lockingExceptions));

#else
            add(testCase(&SharedDataTestSuite::instance));

#endif
        }
#ifdef ENABLE_THREADING
        void instanceThreading()
        {
            SharedData<int> s;
            s.lock();
            shouldEqual(s.isNull(), true);
            s.unlock();
            SharedData<int> s2(new int);
            s2.lock();
            shouldEqual(s2.isNull(), false);
            *(s2.get()) = 10;
            int* pI = new int(5);
            s.lock();
            s.set(pI);
            shouldEqual(s.get(), pI);
            shouldEqual(*(s.get()), 5);
            s.unlock();
            s2.unlock();
        }
#ifndef _WIN32
        void locking()
        {
            SharedData<int> s;
            shouldEqual(s.lockType_==SharedData<int>::NOT_LOCKED, true);
            s.shared_lock();
            shouldEqual(s.lockType_==SharedData<int>::NOT_LOCKED, false);
            shouldEqual(s.lockType_==SharedData<int>::SHARED_LOCK, true);
            s.unlock();
            shouldEqual(s.lockType_==SharedData<int>::SHARED_LOCK, false);
            shouldEqual(s.lockType_==SharedData<int>::NOT_LOCKED, true);
            s.lock();
            shouldEqual(s.lockType_==SharedData<int>::NOT_LOCKED, false);
            shouldEqual(s.lockType_==SharedData<int>::UNIQUE_LOCK, true);
        }
#endif
        void lockingExceptions()
        {
            int* pI = new int(5);
            SharedData<int> s;
            bool thrown = false;
            try {
                s.isNull();
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);
            thrown = false;
            try {
                s.get();
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);
            thrown = false;
            try {
                s.set(pI);
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);
            thrown = false;

            s.shared_lock();
            try {
                s.get();
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, false);
            thrown = false;
            try {
                s.isNull();
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, false);
            thrown = false;
            try {
                s.set(pI);
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, true);
            thrown = false;

            s.lock();
            try {
                s.get();
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, false);
            thrown = false;
            try {
                s.isNull();
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, false);
            thrown = false;
            try {
                s.set(pI);
            } catch (...) {
                thrown = true;
            }shouldEqual(thrown, false);
            thrown = false;
        }
#else
        void instance()
        {
            SharedData<int> s;
            shouldEqual(s.isNull(), true);
            SharedData<int> s2(new int);
            shouldEqual(s2.isNull(), false);
            *(s2.get()) = 10;
            int* pI = new int(5);
            s.set(pI);
            shouldEqual(s.get(), pI);
            shouldEqual(*(s.get()), 5);
        }
#endif
};

/** The main function that runs the tests for class SharedData.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    SharedDataTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

