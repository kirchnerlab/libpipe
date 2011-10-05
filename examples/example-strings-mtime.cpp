/*
 * example-strings-mtime.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *
 */

#include <libpipe/config.hpp>
#include <stdlib.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <set>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <libpipe/Algorithm.hpp>
#include <libpipe/Filter.hpp>
#include <libpipe/Manager.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/BasicFilter.hpp>
#include <libpipe/ModificationTimeManager.hpp>

/** Converts std::string input to uppercase.
 * Although not exceedingly useful, this is a good example of how to write
 * an LIBPIPE algorithm. Basically, there are only two requirements (and one
 * additional option):
 * \li derive from \c libpipe::Algorithm.
 * \li implement the \c update() function.
 * \li optionally, override the \c processRequest() function (if your
 *     implementation does not call the \c update function, you do not
 *     need to implement it).
 *
 * Contrary to other approaches to pipelining (most notably probably the VTK 
 * way), LIBPIPE attempts to minimize hard constraints on the implementations.
 * There is a diverse collection of datatypes and a set of software suites
 * that are being used to process mass spectrometry data. Minimizing the
 * structural imprint that LIBPIPE leaves on applications allows easy cross-suite
 * interfacing and allows for a more rapid algorithmic development cycle.
 */
class UppercaseAlgorithm : public libpipe::Algorithm
{
public:
    /** Constructor.
     * Make sure to call the \c libpipe::Algorithm constructor.
     */
    UppercaseAlgorithm() :
        libpipe::Algorithm(), output_(boost::make_shared<std::string>())
    {
    }

    /** Destructor.
     */
    virtual ~UppercaseAlgorithm()
    {
    }

    /** Runs the algorithm and updates the output data.
     * This is where all the algorithm implementation goes. 
     * @param[in,out] req The request object, forwarded from \c process request.
     */
    libpipe::Request& update(libpipe::Request& req)
    {
        LIBPIPE_REQUEST_TRACE(req, "UppercaseAlgorithm::update: start.");
        output_->clear();
        LIBPIPE_REQUEST_TRACE(req, "UppercaseAlgorithm::update: transforming to uppercase.");
        std::transform(input_->begin(), input_->end(),
            std::back_inserter(*output_), toupper);
        this->updateMTime();
        std::ostringstream oss;
        oss << this->getMTime();
        LIBPIPE_REQUEST_TRACE(req, "UppercaseAlgorithm::update: end at " + oss.str().c_str());
        return req;
    }

    /** Provides access to results.
     * In contrast to more rigid pipeline implementations, LIBPIPE does not
     * impose any constraints on what data types algorithms can share; this is
     * simply done by keeping the request pipeline separate from the
     * input/output flow of the algorithms. In most cases the user knows best
     * which data type is suitable for a problem at hand; there is no reason to
     * take this freedom (and the responsibility from her/him. Algorithms need
     * to specify input and output functions, and it is recommended (but not
     * required) to start the respective function names with 'setInput' and
     * 'getOutput'. 
     *  @returns A handle to the output data of the algorithm.
     */
    boost::shared_ptr<std::string> getOutput()
    {
        return output_;
    }

    /** Allows to connect the output of another algorithm with the input of
     * this algorithm.
     * @see getOutput
     *  
     * @param[in] input A handle (in most cases a (smart) pointer to the data.
     */
    void setInputString(boost::shared_ptr<std::string> input)
    {
        if (input_ != input) {
            input_ = input;
            this->updateMTime();
        }
    }

protected:
    typedef boost::shared_ptr<std::string> StringPtr;

    /** A reference to the input data.
     * This can be a weak pointer or some other kind of reference. In the
     * majority of cases, the algorithm should not attempt to modify this data.
     * There are exceptions (and hence constness is not enforced).
     */
    StringPtr input_;

    /** The output data. 
     * In most cases it is advisable that the memory consumed by this data is
     * owned by the algorithm (or, at least, managed by it).
     */
    StringPtr output_;
};

/** Provides a constant string as output.
 * This is an example of a 'source'. The \c Source algorithm does not require
 * any input and will always provide a predefined string as its output.
 */
class Source : public libpipe::Algorithm
{
public:
    /** Constructor.
     */
    Source() :
        libpipe::Algorithm(), output_(boost::make_shared<std::string>())
    {
        this->setMTime(libpipe::Algorithm::MAX_TIME);
    }

    /** Destructor.
     */
    virtual ~Source()
    {
    }

    void setParamString(const std::string& s)
    {
        *output_ = s;
        // require reexecution on the next call
        this->setMTime(libpipe::Algorithm::MAX_TIME);
    }

    /** Provides access to the output.
     * @return A handle to the output.
     */
    boost::shared_ptr<std::string> getOutput()
    {
        return output_;
    }

    /** Updates the output data (i.e. does nothing).
     * The output is provided as a constant, hence there is nothing to do.
     * @param[in] req The request object.
     * @return The request object.
     */
    libpipe::Request& update(libpipe::Request& req)
    {
        LIBPIPE_REQUEST_TRACE(req, "Source::update: start.");
        // simply update the modification time. Done.
        this->updateMTime();
        std::ostringstream oss;
        oss << this->getMTime();
        LIBPIPE_REQUEST_TRACE(req, "Source::update: end at " + oss.str().c_str());
        return req;
    }

protected:
    /** Holds the output string.
     */
    boost::shared_ptr<std::string> output_;
};

int main(int argc, char *argv[])
{
    using namespace libpipe;

    typedef libpipe::BasicFilter<Source, libpipe::ModificationTimeManager>
            StringCreator;
    typedef libpipe::BasicFilter<UppercaseAlgorithm,
            libpipe::ModificationTimeManager> StringFilter;


    boost::shared_ptr<StringCreator> stringCreator (new StringCreator(
        std::string("StringCreator#1")));
    stringCreator->getAlgorithm()->setParamString("Hello World!");

    boost::shared_ptr<StringFilter> stringFilter (new StringFilter(
        std::string("StringFilter#1")));

    stringFilter->getManager()->connect(boost::dynamic_pointer_cast<Filter>(stringCreator));
    stringFilter->getAlgorithm()->setInputString(
        stringCreator->getAlgorithm()->getOutput());

    Request req(libpipe::Request::UPDATE);
    req.setTraceFlag(true);
    LIBPIPE_REQUEST_TRACE(req, "Starting.");
    try {
        // round 1
        stringFilter->processRequest(req);
        stringFilter->processRequest(req);
        typedef std::vector<std::string> VS;
        VS trace;
        req.getTrace(trace);
        for (VS::const_iterator i = trace.begin(); i != trace.end(); ++i) {
            std::cout << *i << '\n';
        }
        std::cout << "StringCreator out: "
                << *(stringCreator->getAlgorithm()->getOutput()) << '\n';
        std::cout << "StringFilter out: "
                << *(stringFilter->getAlgorithm()->getOutput()) << std::endl;

        // round 2
        req.clearTrace();
        stringCreator->getAlgorithm()->setParamString("Let's do that again!");
        stringFilter->processRequest(req);
        stringFilter->processRequest(req);
        req.getTrace(trace);
        for (VS::const_iterator i = trace.begin(); i != trace.end(); ++i) {
            std::cout << *i << '\n';
        }
        std::cout << "StringCreator out: "
                << *(stringCreator->getAlgorithm()->getOutput()) << '\n';
        std::cout << "StringFilter out: "
                << *(stringFilter->getAlgorithm()->getOutput()) << std::endl;
    } catch (libpipe::RequestException& e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
