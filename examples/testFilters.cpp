/*
 * testFilters.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */


#include <mstk/config.hpp>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <mstk/Algorithm.hpp>
#include <mstk/Filter.hpp>
#include <mstk/Manager.hpp>
#include <mstk/Request.hpp>
#include <mstk/BasicFilter.hpp>
#include <mstk/SimpleManager.hpp>

/** Converts std::string input to uppercase.
 * Although not exceedingly useful, this is a good example of how to write
 * an MSTK algorithm. Basically, there are only two requirements (and one
 * additional option):
 * \li derive from \c mstk::Algorithm.
 * \li implement the \c update() function.
 * \li optionally, override the \c processRequest() function (if your
 *     implementation does not call the \c update function, you do not
 *     need to implement it).
 *
 * Contrary to other approaches to pipelining (most notably probably the VTK 
 * way), MSTK attempts to minimize hard constraints on the implementations.
 * There is a diverse collection of datatypes and a set of software suites
 * that are being used to process mass spectrometry data. Minimizing the
 * structural imprint that MSTK leaves on applications allows easy cross-suite
 * interfacing and allows for a more rapid algorithmic development cycle.
 */
class UppercaseAlgorithm : public mstk::Algorithm
{
  public:
    /** Constructor.
     * Make sure to call the \c mstk::Algorithm constructor.
     */
    UppercaseAlgorithm()
      : mstk::Algorithm(), output_(boost::make_shared<std::string>()) {}
    
    /** Destructor.
     */
    ~UppercaseAlgorithm() {}
    
    /** Runs the algorithm and updates the output data.
     * This is where all the algorithm implementation goes. 
     * @param[inout] req The request object, forwarded from \c process request.
     */
    mstk::Request& update(mstk::Request& req) {
        output_->clear();
        std::transform(input_->begin(), input_->end(), std::back_inserter(*output_), toupper);
        return req;
    }

    /** Provides access to results.
     * In contrast to more rigid pipeline implementations, MSTK does not
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
    boost::shared_ptr<std::string> getOutput() {
        return output_;
    }
    
    /** Allows to connect the output of another algorithm with the input of
     * this algorithm.
     * @see getOutput
     *  
     * @param[in] input A handle (in most cases a (smart) pointer to the data.
     */
    void setInputString(boost::shared_ptr<std::string> input)  {
        input_ = input;
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
class Source : public mstk::Algorithm
{
  public:
    /** Constructor.
     */
    Source() : mstk::Algorithm(), output_(boost::make_shared<std::string>()) {}

    /** Destructor.
     */
    ~Source() {}

    void setParamString(const std::string& s) {
        *output_ = s;
    }
    
    /** Provides access to the output.
     * @return A handle to the output.
     */
    boost::shared_ptr<std::string> getOutput() {
       return output_;
    }


    /** Updates the output data (i.e. does nothing).
     * The output is provided as a constant, hence there is nothing to do.
     * @param[in] req The request object.
     * @return The request object.
     */
    mstk::Request& update(mstk::Request& req) {
        return req;
    }

  protected:
    /** Holds the output string.
     */
    boost::shared_ptr<std::string> output_;
};

int main(int argc, char *argv[])
{
    using namespace mstk;

    typedef mstk::BasicFilter<Source, 
      mstk::SimpleManager> StringCreator;
    typedef mstk::BasicFilter<UppercaseAlgorithm, 
      mstk::SimpleManager> StringFilter;

    StringCreator* stringCreator = new StringCreator;
    stringCreator->getAlgorithm()->setParamString("Hello World!");
    StringFilter* stringFilter = new StringFilter;

    stringFilter->getManager()->connect(stringCreator->getManager());
    stringFilter->getAlgorithm()->setInputString(
      stringCreator->getAlgorithm()->getOutput());

    Request req(mstk::Request::UPDATE);
    stringFilter->getManager()->processRequest(req);
    
    std::cout << "StringCreator out: " 
      << *(stringCreator->getAlgorithm()->getOutput()) << '\n';
    std::cout << "StringFilter out: " 
      << *(stringFilter->getAlgorithm()->getOutput()) << std::endl;
    delete stringFilter;
    delete stringCreator;

    return EXIT_SUCCESS;
}
