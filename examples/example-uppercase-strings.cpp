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
#include <stdlib.h>
#include <exception>
#include <iostream>
#include <set>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <libpipe/ctc/Algorithm.hpp>
#include <libpipe/ctc/Filter.hpp>
#include <libpipe/ctc/Manager.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/ctc/BasicFilter.hpp>
#include <libpipe/ctc/SharedData.hpp>
#include <libpipe/ctc/Pipeline.hpp>

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
class UppercaseAlgorithm : public libpipe::ctc::Algorithm
{
    public:
        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        UppercaseAlgorithm() :
            libpipe::ctc::Algorithm(), output_(
                    boost::make_shared<libpipe::ctc::SharedData<std::string> >(
                        new std::string))
        {
        }

        /** Destructor.
         */
        virtual ~UppercaseAlgorithm()
        {
            std::cout
                    << "\033[22;32m Uppercase Algorithm destroyed with input: "
                    << *input_->get() << "\t and output: " << *output_->get()
                    << "\e[m" << std::endl;
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        libpipe::Request& update(libpipe::Request& req)
        {
            LIBPIPE_PIPELINE_TRACE(req, "UppercaseAlgorithm::update: start.");
            output_->get()->clear();
            LIBPIPE_PIPELINE_TRACE(req,
                "UppercaseAlgorithm::update: transforming to uppercase.");
            std::transform(input_->get()->begin(), input_->get()->end(),
                std::back_inserter(*output_->get()), toupper);
            LIBPIPE_PIPELINE_TRACE(req, "UppercaseAlgorithm::update: end.");
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
        boost::shared_ptr<libpipe::ctc::SharedData<std::string> > getOutput()
        {
            return output_;
        }

        /** Allows to connect the output of another algorithm with the input of
         * this algorithm.
         * @see getOutput
         *
         * @param[in] input A handle (in most cases a (smart) pointer to the data.
         */
        void setInput(
            boost::shared_ptr<libpipe::ctc::SharedData<std::string> > input)
        {
            input_ = input;
        }

    protected:
        typedef boost::shared_ptr<libpipe::ctc::SharedData<std::string> > StringPtr;

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

/** Converts std::string input to lowercase.
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
class LowercaseAlgorithm : public libpipe::ctc::Algorithm
{
    public:
        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        LowercaseAlgorithm() :
            libpipe::ctc::Algorithm(), output_(
                    boost::make_shared<libpipe::ctc::SharedData<std::string> >(
                        new std::string))
        {
        }

        /** Destructor.
         */
        virtual ~LowercaseAlgorithm()
        {
            std::cout
                    << "\033[22;32m Lowercase Algorithm destroyed with input: "
                    << *input_->get() << "\t and output: " << *output_->get()
                    << "\e[m" << std::endl;
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        libpipe::Request& update(libpipe::Request& req)
        {
            LIBPIPE_PIPELINE_TRACE(req, "LowercaseAlgorithm::update: start.");
            output_->get()->clear();
            LIBPIPE_PIPELINE_TRACE(req,
                "LowercaseAlgorithm::update: transforming to uppercase.");
            std::transform(input_->get()->begin(), input_->get()->end(),
                std::back_inserter(*output_->get()), tolower);
            LIBPIPE_PIPELINE_TRACE(req, "LowercaseAlgorithm::update: end.");
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
        boost::shared_ptr<libpipe::ctc::SharedData<std::string> > getOutput()
        {
            return output_;
        }

        /** Allows to connect the output of another algorithm with the input of
         * this algorithm.
         * @see getOutput
         *
         * @param[in] input A handle (in most cases a (smart) pointer to the data.
         */
        void setInput(
            boost::shared_ptr<libpipe::ctc::SharedData<std::string> > input)
        {
            input_ = input;
        }

    protected:
        typedef boost::shared_ptr<libpipe::ctc::SharedData<std::string> > StringPtr;

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

/** Combines the input strings to one string.
 *
 */
class CombineAlgorithm : public libpipe::ctc::Algorithm
{
    public:
        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        CombineAlgorithm() :
                libpipe::ctc::Algorithm(), output_(
                    boost::make_shared<libpipe::ctc::SharedData<std::string> >(
                        new std::string))
        {
        }

        /** Destructor.
         */
        virtual ~CombineAlgorithm()
        {
            std::cout << "\033[22;32m Combine Algorithm destroyed with input: "
                    << *input1_->get() << " and " << *input2_->get()
                    << "\t and output: " << *output_->get() << "\e[m"
                    << std::endl;
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        libpipe::Request& update(libpipe::Request& req)
        {
            LIBPIPE_PIPELINE_TRACE(req, "CombineAlgorithm::update: start.");
            output_->get()->clear();
            LIBPIPE_PIPELINE_TRACE(req,
                "CombineAlgorithm::update: combining inputs");
            combine(output_);
            LIBPIPE_PIPELINE_TRACE(req, "CombineAlgorithm::update: end.");
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
        boost::shared_ptr<libpipe::ctc::SharedData<std::string> > getOutput()
        {
            return output_;
        }

        /** Allows to connect the output of another algorithm with the input of
         * this algorithm.
         * @see getOutput
         *
         * @param[in] input A handle (in most cases a (smart) pointer to the data.
         */
        void setInput1(
            boost::shared_ptr<libpipe::ctc::SharedData<std::string> > input)
        {
            input1_ = input;
        }

        void setInput2(
            boost::shared_ptr<libpipe::ctc::SharedData<std::string> > input)
        {
            input2_ = input;
        }

    protected:
        typedef boost::shared_ptr<libpipe::ctc::SharedData<std::string> > StringPtr;

        /** A reference to the input data.
         * This can be a weak pointer or some other kind of reference. In the
         * majority of cases, the algorithm should not attempt to modify this data.
         * There are exceptions (and hence constness is not enforced).
         */
        StringPtr input1_;
        StringPtr input2_;
        /** The output data.
         * In most cases it is advisable that the memory consumed by this data is
         * owned by the algorithm (or, at least, managed by it).
         */
        StringPtr output_;
    private:
        void combine(
            boost::shared_ptr<libpipe::ctc::SharedData<std::string> > result)
        {
            result->get()->append(*input1_->get());
            result->get()->append(*input2_->get());
        }

};

/** cipher the string with ROT13
 *
 */

class ROT13Algorithm : public libpipe::ctc::Algorithm
{
    public:

        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        ROT13Algorithm() :
                libpipe::ctc::Algorithm(), output_(
                    boost::make_shared<libpipe::ctc::SharedData<std::string> >(
                        new std::string))
        {
        }

        /** virtual Destructor
         */
        virtual ~ROT13Algorithm()
        {
            if (input_) {
                std::cout << "\033[22;32m ROT13 destroyed with input: "
                        << *input_->get() << "\t and output: "
                        << *output_->get() << "\e[m" << std::endl;
            } else {
                std::cout << "\033[22;32m ROT13 destroyed with input: " << ""
                        << "\t and output: " << *output_->get() << "\e[m"
                        << std::endl;
            }

        }

        /** Runs the algorithm and updates the output data.
         * If the request type is DELETE the input gets deleted.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        libpipe::Request& update(libpipe::Request& req)
        {
            if (req.is(libpipe::Request::UPDATE) and this->needUpdate()) {
                LIBPIPE_PIPELINE_TRACE(req, "ROT13Algorithm::update: start.");
                output_.get()->get()->clear();
                LIBPIPE_PIPELINE_TRACE(req,
                    "ROT13Algorithm::update: transforming with ROT13.");
                rot13(input_, output_);
                LIBPIPE_PIPELINE_TRACE(req, "ROT13Algorithm::update: end.");

            } else if (req.is(libpipe::Request::DELETE)) {
                input_.reset();
                LIBPIPE_PIPELINE_TRACE(req,
                    "ROT13Algorithm::update: deleted the input");
            }
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

        boost::shared_ptr<libpipe::ctc::SharedData<std::string> > getOutput()
        {
            return output_;
        }

        /** Allows to connect the output of another algorithm with the input of
         * this algorithm.
         * @see getOutput
         *
         * @param[in] input A handle (in most cases a (smart) pointer to the data.)
         */
        void setInput(
            boost::shared_ptr<libpipe::ctc::SharedData<std::string> > input)
        {
            input_ = input;
        }
    protected:

        typedef boost::shared_ptr<libpipe::ctc::SharedData<std::string> > StringPtr;
        /** The output data.
         * In most cases it is advisable that the memory consumed by this data is
         * owned by the algorithm (or, at least, managed by it).
         */
        StringPtr output_;

        /** A reference to the input data.
         * This can be a weak pointer or some other kind of reference. In the
         * majority of cases, the algorithm should not attempt to modify this data.
         * There are exceptions (and hence constness is not enforced).
         */
        StringPtr input_;

    private:

        /**
         * Function to calculate the ROT13 cipher
         * @param[in] str A handle to the input string
         * @param[out] result A handle to the ciphered input
         */
        void rot13(boost::shared_ptr<libpipe::ctc::SharedData<std::string> > str,
            boost::shared_ptr<libpipe::ctc::SharedData<std::string> > result)
        {
            static std::string const lcalph = "abcdefghijklmnopqrstuvwxyz",
                    ucalph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

            std::string::size_type pos;

            result->get()->reserve(str->get()->length());

            for (std::string::const_iterator it = str->get()->begin();
                    it != str->get()->end(); ++it) {
                if ((pos = lcalph.find(*it)) != std::string::npos)
                    result->get()->push_back(lcalph[(pos + 13) % 26]);
                else if ((pos = ucalph.find(*it)) != std::string::npos)
                    result->get()->push_back(ucalph[(pos + 13) % 26]);
                else
                    result->get()->push_back(*it);
            }
        }
};

/** Provides a constant string as output.
 * This is an example of a 'source'. The \c Source algorithm does not require
 * any input and will always provide a predefined string as its output.
 */
class Source : public libpipe::ctc::Algorithm
{
    public:
        /** Constructor.
         */
        Source() :
                libpipe::ctc::Algorithm(), output_(
                    boost::make_shared<libpipe::ctc::SharedData<std::string> >(
                        new std::string))
        {
        }

        /** Destructor.
         */
        virtual ~Source()
        {
            std::cout << "\033[22;32m Source destroyed with output: "
                    << *output_->get() << "\e[m" << std::endl;
        }

        void setParamString(const std::string& s)
        {
            *output_->get() = s;
        }

        /** Provides access to the output.
         * @return A handle to the output.
         */
        boost::shared_ptr<libpipe::ctc::SharedData<std::string> > getOutput()
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
            LIBPIPE_PIPELINE_TRACE(req, "providing input.");
            return req;
        }

    protected:
        /** Holds the output string.
         */
        boost::shared_ptr<libpipe::ctc::SharedData<std::string> > output_;

};

libpipe::ctc::Pipeline generatePipeline()
{

    using namespace libpipe::ctc;

    typedef BasicFilter<Source, Manager> StringCreator;
    typedef BasicFilter<UppercaseAlgorithm, Manager> StringFilterUp;
    typedef BasicFilter<ROT13Algorithm, Manager> ROTDecrypter;
    typedef BasicFilter<CombineAlgorithm, Manager> Combiner;
    typedef BasicFilter<LowercaseAlgorithm, Manager> StringFilterLow;

    boost::shared_ptr<StringFilterLow> lowerFilter(
        new StringFilterLow(std::string("Lowercase Filter")));

    boost::shared_ptr<StringCreator> stringCreator(
        new StringCreator(std::string("The Source")));
    boost::shared_ptr<StringFilterUp> stringFilter(
        new StringFilterUp(std::string("Filter #1")));
    boost::shared_ptr<ROTDecrypter> rotDecryper(
        new ROTDecrypter(std::string("ROT Decrypter")));
    boost::shared_ptr<ROTDecrypter> rotDecryper1(
        new ROTDecrypter(std::string("ROT Decrypter 1")));
    boost::shared_ptr<Combiner> combiner(
        new Combiner(std::string("Combiner")));

    stringCreator->getAlgorithm()->setParamString(
        "Hello World! I am a very long string to see how much memory is freed by deleting the objects");

    stringFilter->getManager()->connect(
        boost::dynamic_pointer_cast<Filter>(stringCreator));
    stringFilter->getAlgorithm()->setInput(
        stringCreator->getAlgorithm()->getOutput());

    rotDecryper->getManager()->connect(
        boost::dynamic_pointer_cast<Filter>(stringFilter));
    rotDecryper->getAlgorithm()->setInput(
        stringFilter->getAlgorithm()->getOutput());

    rotDecryper1->getManager()->connect(
        boost::dynamic_pointer_cast<Filter>(rotDecryper));
    rotDecryper1->getAlgorithm()->setInput(
        rotDecryper->getAlgorithm()->getOutput());

    combiner->getManager()->connect(
        boost::dynamic_pointer_cast<Filter>(rotDecryper));
    combiner->getManager()->connect(
        boost::dynamic_pointer_cast<Filter>(rotDecryper1));
    combiner->getAlgorithm()->setInput1(
        rotDecryper->getAlgorithm()->getOutput());
    combiner->getAlgorithm()->setInput2(
        rotDecryper1->getAlgorithm()->getOutput());

    lowerFilter->getManager()->connect(
        boost::dynamic_pointer_cast<Filter>(combiner));
    lowerFilter->getAlgorithm()->setInput(
        combiner->getAlgorithm()->getOutput());


    // generate the pipeline
    Pipeline pipe;

    libpipe::Request req(libpipe::Request::UPDATE);
    pipe.setTraceFlag(true);

    pipe.push(req, boost::dynamic_pointer_cast<Filter>(lowerFilter));

    libpipe::Request reqDelete(libpipe::Request::DELETE);
    pipe.setTraceFlag(true);

    pipe.push(reqDelete, boost::dynamic_pointer_cast<Filter>(lowerFilter));

    libpipe::Request req1(libpipe::Request::UPDATE);
    pipe.setTraceFlag(true);

    pipe.push(req1, boost::dynamic_pointer_cast<Filter>(lowerFilter));

    return pipe;
}

int main(int argc, char *argv[])
{
    libpipe::ctc::Pipeline pipeline;

    pipeline=generatePipeline();
    pipeline.run();

    typedef std::vector<std::string> VS;
    VS trace;
    trace=pipeline.getTrace();
    for (VS::const_iterator i = trace.begin(); i != trace.end(); ++i) {
        std::cout << *i << '\n';
    }

    return EXIT_SUCCESS;
}

