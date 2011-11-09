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

#ifndef __LIBPIPE_INCLUDE_LIBPIPE_CTC_FILTER_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_CTC_FILTER_HPP__

#include <libpipe/config.hpp>
#include <string>
#include <libpipe/Request.hpp>

#include <boost/noncopyable.hpp>

namespace libpipe {
namespace ctc {

// forward declarations
class Algorithm;
class Manager;

/** The base class for all LIBPIPE filters. Filters are non-copyable by
 * default.
 */
class Filter : private boost::noncopyable
{
public:
    /** Constructor.
     */
    Filter(const std::string&);

    /** Pure virtual destructor.
     */
    virtual ~Filter();

    /** Processes a request.
     * This method forwards the request to the Algorithm and Manager objects.
     * @param[in] req The request object.
     * @return The request object with processing information filled out.
     */
    virtual void processRequest(Request& req);

    /** Returns a  pointer to the algorithm object.
     * @return A pointer to the algorithm object.
     */
    virtual Algorithm* getAlgorithm();

    /** Returns a  pointer to the Manager object.
     * @return A pointer to the Manager object.
     */
    virtual Manager* getManager();

    /** Returns the name of the filter.
     * @return The name of the filter.
     */
    std::string getName() const;

    /** Set the name of the filter.
     * @param[in] name The name of the filter.
     */
    void setName(const std::string& name);

protected:
    /** Set the algorithm that should be used for this filter.
     * @param[in] alg Pointer to the Algorithm object.
     */
    void setAlgorithm(Algorithm* alg);

    /** Set the manager that manages the filter.
     * @param[in] manager Pointer to the Manager object.
     */
    void setManager(Manager* manager);

private:
    /** A pointer to the algorithm that is part of the filter.
     */
    Algorithm* algorithm_;

    /** A pointer to the manager that is part of the filter.
     */
    Manager* manager_;

    /** Holds the name of the filter.
     */
    std::string name_;
};

} // end namespace ctc
} // end namespace libpipe

#endif //__LIBPIPE_INCLUDE_LIBPIPE_CTC_FILTER_HPP__

