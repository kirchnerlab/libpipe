/*
 * example-rtc.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */

#include <libpipe/config.hpp>
#include <stdlib.h>
#include <exception>
#include <iostream>
#include <set>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Filter.hpp>
#include <libpipe/rtc/Manager.hpp>
#include <libpipe/rtc/ManagerFactory.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>
#include <libpipe/utilities/Exception.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/rtc/SharedData.hpp>

#include <libpipe/rtc/PipelineLoader.hpp>

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
class UppercaseAlgorithm : public libpipe::rtc::Algorithm
{
    public:
        // use convenience typedefs to avoid cluttering up the code
        typedef std::string String;
        typedef libpipe::rtc::SharedData<String> SharedString;

        static Algorithm* create()
        {
            return new UppercaseAlgorithm;
        }

        /** Destructor.
         */
        virtual ~UppercaseAlgorithm()
        {
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         * @return The request
         */
        void update(libpipe::Request& req)
        {

            LIBPIPE_PREPARE_READ_ACCESS(input_, dataIn_, String, "StringInput");
            LIBPIPE_PREPARE_WRITE_ACCESS(output_, dataOut_, String,
                "StringOutput");

            LIBPIPE_PIPELINE_TRACE("UppercaseAlgorithm::update: start.");
            dataOut_.clear();
            LIBPIPE_PIPELINE_TRACE(
                "UppercaseAlgorithm::update: transforming to uppercase.");
            std::transform(dataIn_.begin(), dataIn_.end(),
                std::back_inserter(dataOut_), toupper);
            LIBPIPE_PIPELINE_TRACE("UppercaseAlgorithm::update: end.");

#ifdef ENABLE_THREADING
            output_->unlock();
            input_->unlock();
#endif
        }

    protected:
        /** Constructor.
         * Make sure to call the \c libpipe::rtc::Algorithm constructor.
         */
        UppercaseAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringInput"] = boost::make_shared<
                    SharedString>();
            ports_["StringOutput"] = boost::make_shared<
                    SharedString >(new std::string);
        }

    private:

        /** registers the Algorithm in the factory
         * @return true is registration was successful
         */
        static const bool registerLoader()
        {
            std::string ids = "UppercaseAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                UppercaseAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;

};

const bool UppercaseAlgorithm::registered_ = registerLoader();

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
class LowercaseAlgorithm : public libpipe::rtc::Algorithm
{
    public:
        // use convenience typedefs to avoid cluttering up the code
        typedef std::string String;
        typedef libpipe::rtc::SharedData<String> SharedString;

        static Algorithm* create()
        {
            return new LowercaseAlgorithm;
        }
        /** Destructor.
         */
        virtual ~LowercaseAlgorithm()
        {
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         * @return The request
         */
        void update(libpipe::Request& req)
        {
            LIBPIPE_PREPARE_READ_ACCESS(input_, dataIn_, String, "StringInput");
            LIBPIPE_PREPARE_WRITE_ACCESS(output_, dataOut_, String,
                "StringOutput");

            LIBPIPE_PIPELINE_TRACE("LowercaseAlgorithm::update: start.");
            dataOut_.clear();

            LIBPIPE_PIPELINE_TRACE(
                "LowercaseAlgorithm::update: transforming to uppercase.");
            std::transform(dataIn_.begin(), dataIn_.end(),
                std::back_inserter(dataOut_), tolower);

            LIBPIPE_PIPELINE_TRACE("LowercaseAlgorithm::update: end.");
#ifdef ENABLE_THREADING
            output_->unlock();
            input_->unlock();
#endif
        }

    protected:

    private:
        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        LowercaseAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringInput"] = boost::make_shared<
                    SharedString >();
            ports_["StringOutput"] = boost::make_shared<
                    SharedString >(new std::string);
        }
        /** registers the Algorithm in the factory
         * @return true is registration was successful
         */
        static const bool registerLoader()
        {
            std::string ids = "LowercaseAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                LowercaseAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;

};

const bool LowercaseAlgorithm::registered_ = registerLoader();

/** Combines the input strings to one string.
 *
 */
class CombineAlgorithm : public libpipe::rtc::Algorithm
{
    public:
        // use convenience typedefs to avoid cluttering up the code
        typedef std::string String;
        typedef libpipe::rtc::SharedData<String> SharedString;

        static Algorithm* create()
        {
            return new CombineAlgorithm;
        }

        /** Destructor.
         */
        virtual ~CombineAlgorithm()
        {

            LIBPIPE_PREPARE_READ_ACCESS(input1_, dataIn1_, String,
                "StringInput1");
            LIBPIPE_PREPARE_READ_ACCESS(input2_, dataIn2_, String,
                "StringInput2");
            LIBPIPE_PREPARE_WRITE_ACCESS(output_, dataOut_, String,
                "StringOutput");

            std::cout << "\033[22;32m Combine Algorithm destroyed with input: "
                    << dataIn1_ << " and " << dataIn2_
                    << "\t and output: " << dataOut_ << "\e[m"
                    << std::endl;
#ifdef ENABLE_THREADING
            output_->unlock();
            input1_->unlock();
            input2_->unlock();
#endif
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         * @return The request
         */
        void update(libpipe::Request& req)
        {
            LIBPIPE_PREPARE_READ_ACCESS(input1_, dataIn1_, String,
                "StringInput1");
            LIBPIPE_PREPARE_READ_ACCESS(input2_, dataIn2_, String,
                "StringInput2");
            LIBPIPE_PREPARE_WRITE_ACCESS(output_, dataOut_, String,
                "StringOutput");

            LIBPIPE_PIPELINE_TRACE("CombineAlgorithm::update: start.");
            dataOut_.clear();

            LIBPIPE_PIPELINE_TRACE(
                "CombineAlgorithm::update: combining inputs");
            combine(dataOut_, dataIn1_, dataIn2_);
            LIBPIPE_PIPELINE_TRACE("CombineAlgorithm::update: end.");
#ifdef ENABLE_THREADING
            output_->unlock();
            input1_->unlock();
            input2_->unlock();
#endif
        }

    protected:

    private:
        /** Combines two inputs
         * @param result The result
         */
        void combine(String& result,
            const String& input1_,
            const String& input2_)
        {
            result.append(input1_);
            result.append(input2_);
        }

        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        CombineAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringInput1"] = boost::make_shared<
                    SharedString >();
            ports_["StringInput2"] = boost::make_shared<
                    SharedString >();
            ports_["StringOutput"] = boost::make_shared<
                    SharedString >(new std::string);

        }
        /** registers the Algorithm in the factory
         * @return true is registration was successful
         */
        static const bool registerLoader()
        {
            std::string ids = "CombineAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                CombineAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;

};

const bool CombineAlgorithm::registered_ = registerLoader();

/** cipher the string with ROT13
 *
 */

class ROT13Algorithm : public libpipe::rtc::Algorithm
{
    public:
        // use convenience typedefs to avoid cluttering up the code
        typedef std::string String;
        typedef libpipe::rtc::SharedData<String> SharedString;

        static Algorithm* create()
        {
            return new ROT13Algorithm;
        }

        /** virtual Destructor
         */
        virtual ~ROT13Algorithm()
        {

        }

        /** Runs the algorithm and updates the output data.
         * If the request type is DELETE the input gets deleted.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         * @return The request
         */
        void update(libpipe::Request& req)
        {

            LIBPIPE_PREPARE_READ_ACCESS(input_, dataIn_, String,
                "StringInput");
            LIBPIPE_PREPARE_WRITE_ACCESS(output_, dataOut_, String,
                "StringOutput");

            if (req.is(libpipe::Request::UPDATE) && this->needUpdate()) {
                LIBPIPE_PIPELINE_TRACE("ROT13Algorithm::update: start.");
                dataOut_.clear();
                LIBPIPE_PIPELINE_TRACE(
                    "ROT13Algorithm::update: transforming with ROT13.");
                rot13(dataIn_, dataOut_);

                LIBPIPE_PIPELINE_TRACE("ROT13Algorithm::update: end.");

            } else if (req.is(libpipe::Request::DELETE)) {
                input_.reset();
                LIBPIPE_PIPELINE_TRACE(
                    "ROT13Algorithm::update: deleted the input");
            }
#ifdef ENABLE_THREADING
            output_->unlock();
            input_->unlock();
#endif
        }

    protected:

    private:

        /**
         * Function to calculate the ROT13 cipher
         * @param[in] str A handle to the input string
         * @param[out] result A handle to the ciphered input
         */
        void rot13(const String& str, String& result)
        {
            static std::string const lcalph = "abcdefghijklmnopqrstuvwxyz",
                    ucalph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

            std::string::size_type pos;

            result.reserve(str.length());

            for (std::string::const_iterator it = str.begin(); it != str.end();
                    ++it) {
                if ((pos = lcalph.find(*it)) != std::string::npos)
                    result.push_back(lcalph[(pos + 13) % 26]);
                else if ((pos = ucalph.find(*it)) != std::string::npos)
                    result.push_back(ucalph[(pos + 13) % 26]);
                else
                    result.push_back(*it);
            }
        }

        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        ROT13Algorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringInput"] = boost::make_shared<SharedString>();
            ports_["StringOutput"] = boost::make_shared<SharedString>(
                new std::string);
        }
        /** registers the Algorithm in the factory
         * @return true is registration was successful
         */
        static const bool registerLoader()
        {
            std::string ids = "ROT13Algorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                ROT13Algorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;

};

const bool ROT13Algorithm::registered_ = registerLoader();

/** Provides a constant string as output.
 * This is an example of a 'source'. The \c Source algorithm does not require
 * any input and will always provide a predefined string as its output.
 */
class Source : public libpipe::rtc::Algorithm
{
    public:
        // use convenience typedefs to avoid cluttering up the code
        typedef std::string String;
        typedef libpipe::rtc::SharedData<String> SharedString;

        static Algorithm* create()
        {
            return new Source;
        }

        /** Destructor.
         */
        virtual ~Source()
        {
        }

        /** Updates the output data (i.e. does nothing).
         * The output is provided as a constant, hence there is nothing to do.
         * @param[in] req The request object.
         * @return The request object.
         */
        void update(libpipe::Request& req)
        {

            LIBPIPE_PREPARE_WRITE_ACCESS(output_, tempOut, String,
                "StringOutput");

            String temp = parameters_.get<String>("SourceString")
                    + parameters_.get<String>("SourceString2");

            tempOut = temp;

#ifdef ENABLE_THREADING
            output_->unlock();
#endif

        }

    protected:

    private:
        /** Constructor.
         */
        Source() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringOutput"] = boost::make_shared<SharedString>(
                new std::string(""));
        }
        /** registers the Algorithm in the factory
         * @return true is registration was successful
         */
        static const bool registerLoader()
        {
            std::string ids = "Source";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                Source::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;

};

const bool Source::registered_ = registerLoader();

int main(int argc, char *argv[])
{
    using namespace libpipe::rtc;

    std::map<std::string, std::string> inputFiles;
    inputFiles["FilterInput"] = "inputFileFilterJSON.txt";
    inputFiles["ConnectionInput"] = "inputFileConnectionJSON.txt";
    inputFiles["PipelineInput"] = "inputFilePipelineJSON.txt";
    inputFiles["ParameterInput"] = "inputFileParametersJSON.txt";

    Pipeline pipeline;
    try {
        PipelineLoader loader(inputFiles);
        pipeline = loader.getPipeline();
    } catch (libpipe::utilities::Exception& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        pipeline.run();
    } catch (libpipe::utilities::Exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<std::string> trace;
    trace = pipeline.getTrace();
    for (std::vector<std::string>::const_iterator i = trace.begin();
            i != trace.end(); ++i) {
        std::cout << *i << '\n';
    }

    std::cout
            << "All output after this is due to automatically called destructors."
            << std::endl;

    return EXIT_SUCCESS;

}

