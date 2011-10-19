/*
 * ModificationTimeManager.hpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_MODIFICATIONTIMEMANAGER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_MODIFICATIONTIMEMANAGER_HPP__

#include <libpipe/config.hpp>

#include <libpipe/Request.hpp>
#include <libpipe/Manager.hpp>

namespace libpipe {

/** A manager class that makes use of the modification time information of 
 * the algoritms it manages.
 * :TODO:01/01/2011 11:12:42:mkirchner: fill in details how it works.
 */
class ModificationTimeManager : public Manager
{
public:
    /** Constructor.
     */
    ModificationTimeManager();

    /** Destructor.
     * Virtual, to allow subclassing.
     */
    virtual ~ModificationTimeManager();

    /** Processes a request, taking into account the current modification time
     * of the \c Manager's algorithm.
     * @param [in,out] req The request object.
     * @return A (potentially modified) request object.
     */
    virtual Request& processRequest(Request& req);
};

}

#endif   

