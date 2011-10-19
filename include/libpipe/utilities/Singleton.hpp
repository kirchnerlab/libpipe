/*
 * Singleton.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 * Copyright (c) 2008 Thorben Kroeger
 *
 */

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_SINGLETON_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_SINGLETON_HPP__

#include <libpipe/config.hpp>

#include <exception>
namespace utilities {
/** Singleton holder template class.
 * Template class to create singletons. A singleton of type SinglImpl is
 * created by
 *
 * typedef Singleton<SinglImpl> Singl;
 */
template<class T>
class Singleton
{
    public:
        /** Returns exactly one instance of the object.
         * @return An instance of the object
         */
        static T& instance();

        /** Destructor
         */
        ~Singleton();
    private:
        /** Constructor
         */
        Singleton();

        /** Constructor
         * @param S A singleton
         */
        Singleton(const Singleton& S);

        /** Assignment operator
         * @param S A singleton
         * @return The same singleton
         */
        Singleton& operator=(const Singleton& S);

        /** Create methode
         */
        static void create();

        /** Pointer to the instance
         */
        static T* pInstance_;

        /** true if the singleton was destroyed
         */
        static bool destroyed_;

};

/** Returns the unique instance of class T. If it was already
 *  deleted an exception is thrown. If the class T was never used
 *  before a new instance is generated.
 *
 * @return Unique instance of class T
 */
template<class T> T& Singleton<T>::instance()
{
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

template<class T> Singleton<T>::~Singleton()
{
    pInstance_ = 0;
    destroyed_ = true;
}

template<class T> void Singleton<T>::create()
{
    static T theInstance;
    pInstance_ = &theInstance;
}

template<class T> T* Singleton<T>::pInstance_ = 0;
template<class T> bool Singleton<T>::destroyed_ = false;

}
#endif /* __LIBPIPE_INCLUDE_LIBPIPE_UTILITIES_SINGLETON_HPP__ */
