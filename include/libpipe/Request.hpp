/*
 * Request.hpp
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_REQUEST_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_REQUEST_HPP__

#include <libpipe/config.hpp>

#include <vector>
#include <string>
#include <ctime>
#include <libpipe/RequestException.hpp>

/** Macro that add an entry to a requests trace.
 * This is just for convenience.
 */
#define LIBPIPE_REQUEST_TRACE(req, str) \
  if (req.getTraceFlag()) \
  req.addTrace(std::string(__FUNCTION__) + ": " + str)

namespace libpipe {

/** A request object.
 * The request object is used to transfer requests between filters. 
 */
class Request
{
public:
    /** Defines the request type.
     * UPDATE for updating the filters
     * DELETE for deleting the filters
     */
    enum Type
    {
        UPDATE = 0,
        DELETE = 1
    };

    /** Constructor.
     * Requires a request type.
     * @param[in] t The type of the request.
     */
    Request(const Type& t);

    /** Destructor.
     * Virtual, to allow subclassing.
     */
    virtual ~Request();

    /** Tests the type of a request.
     * @param[in] t A request type.
     */
    bool is(const Type& t);

    /** Returns the state of the trace flag.
     * If the trace flag is on, clients should add trace information
     * while processing the request, using addTrace().
     * @return The state if the trace flag (true == on).
     */
    bool getTraceFlag() const;

    /** Set the state of the trace flag.
     * This allows to switch tracing on and off. 
     * @param[in] tf The new trace flag setting (true == on).
     */
    void setTraceFlag(const bool tf);

    /** Returns all traces collected in the Request object.
     * @param[out] trace All collected trace information.
     */
    void getTrace(std::vector<std::string>& trace);

    /** Add trace information to the request object.
     * Currently the request object simply collects std::strings.
     * @param[in] t Trace information.
     */
    void addTrace(const std::string& t);

    /** Clears all trace information from the Request object.
     */
    void clearTrace();

protected:

    /** The request type.
     * @see Type
     */
    Type type_;

    /** Trace status.
     * If true, clients receiving the request should store
     * trace information using addTrace().
     * @see addTrace
     */
    bool traceFlag_;

    /** Trace information.
     */
    std::vector<std::string> trace_;
};

} // namespace libpipe

#endif

