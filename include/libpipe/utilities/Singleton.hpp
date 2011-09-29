/*
 * Singleton.hpp
 *
 * Copyright (c) 2010 Marc Kirchner <marc.kirchner@childrens.harvard.edu>
 * Copyright (c) 2008 Thorben Kroeger <thorben.kroeger@iwr.uni-heidelberg.de>
 *
 * This file is part of ms++.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without  restriction, including without limitation the rights
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_
#include <exception>

/** Singleton holder template class.
 * Template class to create singletons. A singleton of type SinglImpl is
 * created by
 *
 * typedef Singleton<SinglImpl> Singl;
 */
template <class T>
class Singleton {
    public:
        static T& instance();
        ~Singleton();
    private:
        Singleton();
        Singleton(const Singleton&);
        Singleton& operator=(const Singleton&);

        static void create();
        static T* pInstance_;
        static bool destroyed_;

};

/** Returns the unique instance of class T. If it was already
 *  deleted an exception is thrown. If the class T was never used
 *  before a new instance is generated.
 *
 * @return Unique instance of class T
 */
template<class T> T& Singleton<T>::instance() {
    if (!pInstance_) {
        if (destroyed_) {
            // dead reference
            throw std::exception();
        } else {
            // initial creation
            create();
        }
    }
    return *pInstance_;
}

template <class T> Singleton<T>::~Singleton() {
    pInstance_ = 0;
    destroyed_ = true;
}

template <class T> void Singleton<T>::create() {
    static T theInstance;
    pInstance_ = &theInstance;
}

template <class T> T* Singleton<T>::pInstance_ = 0;
template <class T> bool Singleton<T>::destroyed_ = false;

#endif /* SINGLETON_HPP_ */
