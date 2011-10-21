/*
 * Exception.hpp
 *
 * Copyright (c) 2011 David Sichau
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_UTILITIES_LIBPIPE_EXCEPTION_HPP__
#define __LIBPIPE_INCLUDE_UTILITIES_LIBPIPE_EXCEPTION_HPP__

#include <exception>
#include <string>

namespace libpipe {
namespace utilities {

/** libpipe expection base class.
 */
class Exception : public std::exception
{
public:
    /** Constructor (C strings).
     *  @param message C-style string error message.
     *                 The string contents are copied upon construction.
     *                 Hence, responsibility for deleting the \c char* lies
     *                 with the caller. 
     */
    explicit Exception(const char* message);

    /** Constructor (C++ STL strings).
     *  @param message The error message.
     */
    explicit Exception(const std::string& message);

    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~Exception() throw ();

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a \c const \c char*. The underlying memory
     *          is in posession of the \c Exception object. Callers \a must
     *          not attempt to free the memory.
     */
    virtual const char* what() const throw ();

protected:
    /** Error message.
     */
    std::string msg_;
};

/** Convenience macros.
 */
#define libpipe_fail(ERROR_MESSAGE) throw libpipe::utilities::Exception(ERROR_MESSAGE)

} // end namespace utilities
} // end namespace libpipe

#endif //__LIBPIPE_INCLUDE_UTILITIES_LIBPIPE_EXCEPTION_HPP__

