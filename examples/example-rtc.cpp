/*
 * testFilters.cpp
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
#include <libpipe/rtc/AlgorithmRTC.hpp>
#include <libpipe/rtc/FilterRTC.hpp>
#include <libpipe/rtc/ManagerRTC.hpp>
#include <libpipe/rtc/LibpipeFactories.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/BasicFilter.hpp>
#include <libpipe/rtc/SharedDataRTC.hpp>

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

        static Algorithm* create()
        {
            return new UppercaseAlgorithm;
        }

        /** Destructor.
         */
        virtual ~UppercaseAlgorithm()
        {

            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
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
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));

            LIBPIPE_REQUEST_TRACE(req, "UppercaseAlgorithm::update: start.");
            output_.get()->get()->clear();
            LIBPIPE_REQUEST_TRACE(req,
                "UppercaseAlgorithm::update: transforming to uppercase.");
            std::transform(input_->get()->begin(), input_->get()->end(),
                std::back_inserter(*output_->get()), toupper);
            LIBPIPE_REQUEST_TRACE(req, "UppercaseAlgorithm::update: end.");
            return req;
        }

    protected:
        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        UppercaseAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringInput"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >();
            ports_["StringOutput"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >(new std::string);

        }

       private:
        static const bool registerLoader()
        {
            std::string ids = "UppercaseAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                UppercaseAlgorithm::create);
        }

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

        static Algorithm* create()
        {
            return new LowercaseAlgorithm;
        }
        /** Destructor.
         */
        virtual ~LowercaseAlgorithm()
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));

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
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));

            LIBPIPE_REQUEST_TRACE(req, "LowercaseAlgorithm::update: start.");
            output_.get()->get()->clear();
            LIBPIPE_REQUEST_TRACE(req,
                "LowercaseAlgorithm::update: transforming to uppercase.");
            std::transform(input_->get()->begin(), input_->get()->end(),
                std::back_inserter(*output_->get()), tolower);
            LIBPIPE_REQUEST_TRACE(req, "LowercaseAlgorithm::update: end.");
            return req;
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
                    libpipe::rtc::SharedData<std::string> >();
            ports_["StringOutput"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >(new std::string);
        }
        static const bool registerLoader()
        {
            std::string ids = "LowercaseAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                LowercaseAlgorithm::create);
        }

        static const bool registered_;

};

const bool LowercaseAlgorithm::registered_ = registerLoader();

/** Combines the input strings to one string.
 *
 */
class CombineAlgorithm : public libpipe::rtc::Algorithm
{
    public:
        static Algorithm* create()
        {
            return new CombineAlgorithm;
        }

        /** Destructor.
         */
        virtual ~CombineAlgorithm()
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input1_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput1"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input2_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput2"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
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

            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input1_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput1"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input2_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput2"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
            LIBPIPE_REQUEST_TRACE(req, "CombineAlgorithm::update: start.");
            output_.get()->get()->clear();
            LIBPIPE_REQUEST_TRACE(req,
                "CombineAlgorithm::update: combining inputs");
            combine(output_);
            LIBPIPE_REQUEST_TRACE(req, "CombineAlgorithm::update: end.");
            return req;
        }

    protected:

    private:
        void combine(
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > result)
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input1_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput1"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input2_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput2"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
            result->get()->append(*input1_->get());
            result->get()->append(*input2_->get());
        }

        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        CombineAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringInput1"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >();
            ports_["StringInput2"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >();
            ports_["StringOutput"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >(new std::string);

        }
        static const bool registerLoader()
        {
            std::string ids = "CombineAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                CombineAlgorithm::create);
        }

        static const bool registered_;

};

const bool CombineAlgorithm::registered_ = registerLoader();

/** cipher the string with ROT13
 *
 */

class ROT13Algorithm : public libpipe::rtc::Algorithm
{
    public:

        static Algorithm* create()
        {
            return new ROT13Algorithm;
        }

        /** virtual Destructor
         */
        virtual ~ROT13Algorithm()
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
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
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
            if (req.is(libpipe::Request::UPDATE) and this->needUpdate()) {
                LIBPIPE_REQUEST_TRACE(req, "ROT13Algorithm::update: start.");
                output_.get()->get()->clear();
                LIBPIPE_REQUEST_TRACE(req,
                    "ROT13Algorithm::update: transforming with ROT13.");
                rot13(input_, output_);
                LIBPIPE_REQUEST_TRACE(req, "ROT13Algorithm::update: end.");

            } else if (req.is(libpipe::Request::DELETE)) {
                input_.reset();
                LIBPIPE_REQUEST_TRACE(req,
                    "ROT13Algorithm::update: deleted the input");
            }
            return req;
        }

    protected:

    private:

        /**
         * Function to calculate the ROT13 cipher
         * @param[in] str A handle to the input string
         * @param[out] result A handle to the ciphered input
         */
        void rot13(
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > str,
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > result)
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

        /** Constructor.
         * Make sure to call the \c libpipe::Algorithm constructor.
         */
        ROT13Algorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringInput"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >();
            ports_["StringOutput"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >(new std::string);
        }
        static const bool registerLoader()
        {
            std::string ids = "ROT13Algorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                ROT13Algorithm::create);
        }

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
        static Algorithm* create()
        {
            return new Source;
        }

        /** Destructor.
         */
        virtual ~Source()
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
            std::cout << "\033[22;32m Source destroyed with output: "
                    << *output_.get()->get() << "\e[m" << std::endl;
        }

        /** Updates the output data (i.e. does nothing).
         * The output is provided as a constant, hence there is nothing to do.
         * @param[in] req The request object.
         * @return The request object.
         */
        libpipe::Request& update(libpipe::Request& req)
        {
            LIBPIPE_REQUEST_TRACE(req, "providing input.");
            return req;
        }

    protected:

    private:
        /** Constructor.
         */
        Source() :
                libpipe::rtc::Algorithm()
        {
            ports_["StringOutput"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::string> >(new std::string);
        }

        static const bool registerLoader()
        {
            std::string ids = "Source";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                Source::create);
        }

        static const bool registered_;

};

const bool Source::registered_ = registerLoader();

int main(int argc, char *argv[])
{
    using namespace libpipe::rtc;

    boost::shared_ptr<Filter> lowerFilter;

    {
        // construct filters and save in map for later identification
        std::map<std::string, boost::shared_ptr<Filter> > filterMap;

        filterMap["LowercaseFilter"] = boost::shared_ptr<Filter>(
            Filter::create("Lowercase Filter", "LowercaseAlgorithm",
                "MangerRTC"));
        filterMap["TheSource"] = boost::shared_ptr<Filter>(
            Filter::create("The Source", "Source", "MangerRTC"));
        filterMap["Filter1"] = boost::shared_ptr<Filter>(
            Filter::create("Filter #1", "UppercaseAlgorithm", "MangerRTC"));
        filterMap["ROTDecrypter"] = boost::shared_ptr<Filter>(
            Filter::create("ROT Decrypter", "ROT13Algorithm", "MangerRTC"));
        filterMap["ROTDecrypter1"] = boost::shared_ptr<Filter>(
            Filter::create("ROT Decrypter 1", "ROT13Algorithm", "MangerRTC"));
        filterMap["Combiner"] = boost::shared_ptr<Filter>(
            Filter::create("Combiner", "CombineAlgorithm", "MangerRTC"));

        //sets input for first Filter
        boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input(
            new SharedData<std::string>());
        input->set(new std::string("Hello World!"));
        filterMap.find("TheSource")->second->getAlgorithm()->setInput(
            "StringOutput", input);

        //Connect ports
        filterMap.find("TheSource")->second->getAlgorithm()->connect(
            filterMap.find("Filter1")->second->getAlgorithm(), "StringInput",
            "StringOutput");

        filterMap.find("Filter1")->second->getAlgorithm()->connect(
            filterMap.find("ROTDecrypter")->second->getAlgorithm(),
            "StringInput", "StringOutput");

        filterMap.find("ROTDecrypter")->second->getAlgorithm()->connect(
            filterMap.find("ROTDecrypter1")->second->getAlgorithm(),
            "StringInput", "StringOutput");

        filterMap.find("ROTDecrypter")->second->getAlgorithm()->connect(
            filterMap.find("Combiner")->second->getAlgorithm(), "StringInput1",
            "StringOutput");

        filterMap.find("ROTDecrypter1")->second->getAlgorithm()->connect(
            filterMap.find("Combiner")->second->getAlgorithm(), "StringInput2",
            "StringOutput");

        filterMap.find("Combiner")->second->getAlgorithm()->connect(
            filterMap.find("LowercaseFilter")->second->getAlgorithm(),
            "StringInput", "StringOutput");


        //Manager connect
        filterMap.find("Filter1")->second->getManager()->connect(
                filterMap.find("TheSource")->second);

        filterMap.find("ROTDecrypter")->second->getManager()->connect(
                filterMap.find("Filter1")->second);

        filterMap.find("ROTDecrypter1")->second->getManager()->connect(
                filterMap.find("ROTDecrypter")->second);

        filterMap.find("Combiner")->second->getManager()->connect(
            filterMap.find("ROTDecrypter")->second);

        filterMap.find("Combiner")->second->getManager()->connect(
                filterMap.find("ROTDecrypter1")->second);

        filterMap.find("LowercaseFilter")->second->getManager()->connect(
                filterMap.find("Combiner")->second);

        // the filter that will be used outside the scope
        lowerFilter = filterMap.find("LowercaseFilter")->second;
    }

    libpipe::Request req(libpipe::Request::UPDATE);
    req.setTraceFlag(true);
    LIBPIPE_REQUEST_TRACE(req, "Starting.");

    try {
        lowerFilter->getManager()->processRequest(req);

    } catch (libpipe::RequestException& e) {
        std::cerr << e.what() << std::endl;
    }

    typedef std::vector<std::string> VS;
    VS trace;
    req.getTrace(trace);
    for (VS::const_iterator i = trace.begin(); i != trace.end(); ++i) {
        std::cout << *i << '\n';
    }

    libpipe::Request reqDelete(libpipe::Request::DELETE);
    reqDelete.setTraceFlag(true);
    LIBPIPE_REQUEST_TRACE(reqDelete, "Starting with DELETE");

    lowerFilter->getManager()->processRequest(reqDelete);

    VS traceDelete;
    reqDelete.getTrace(traceDelete);
    for (VS::const_iterator i = traceDelete.begin(); i != traceDelete.end();
            ++i) {
        std::cout << *i << '\n';
    }

    libpipe::Request req1(libpipe::Request::UPDATE);
    req1.setTraceFlag(true);
    LIBPIPE_REQUEST_TRACE(req1, "Starting.");

    try {
        lowerFilter->getManager()->processRequest(req1);

    } catch (libpipe::RequestException& e) {
        std::cerr << e.what() << std::endl;
    }

    VS trace1;
    req1.getTrace(trace1);
    for (VS::const_iterator i = trace1.begin(); i != trace1.end(); ++i) {
        std::cout << *i << '\n';
    }

    std::cout
            << "\033[22;35m All output after this is due to automatically called destructors. \e[m"
            << std::endl;

    return EXIT_SUCCESS;
}

