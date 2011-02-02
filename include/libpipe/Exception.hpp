/*
 * Exception.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_EXCEPTION_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_EXCEPTION_HPP__

#include <exception>
#include <string>

namespace libpipe {

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
    explicit Exception(const char* message) {
        what_ = message;
    }
    
    /** Constructor (C++ STL strings).
     *  @param message The error message.
     */
    explicit Exception(const std::string& message) {
        what_ = message;
    }
    
    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~Exception() throw() {}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a \c const \c char*. The underlying memory
     *          is in posession of the \c Exception object. Callers \a must
     *          not attempt to free the memory.
     */
    virtual const char * what() const throw() {
        return what_.c_str();
    }
    
  protected:
    /** Error message.
     */
    std::string what_;
};

/** Convenience macros.
 */
#define libpipe_fail(ERROR_MESSAGE) throw libpipe::Exception(ERROR_MESSAGE)

} // namespace libpipe

#endif 

