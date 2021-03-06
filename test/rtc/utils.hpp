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

#ifndef __LIBPIPE_TEST_UTILS_HPP__
#define __LIBPIPE_TEST_UTILS_HPP__
#include <libpipe/config.hpp>

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Manager.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>
#include <libpipe/rtc/SharedData.hpp>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>
#include <libpipe/rtc/Pipeline.hpp>

#include <set>
#include <iostream>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

namespace libpipe {
namespace rtc {

/** An algorithm that does not change its input.
 */
class IdentityRTC : public Algorithm
{
    public:
        static Algorithm* create()
        {
            return new IdentityRTC;
        }

        ~IdentityRTC()
        {
        }
        void update(Request& req)
        {
            LIBPIPE_PIPELINE_TRACE("Identity: copying value.");

            boost::shared_ptr<libpipe::rtc::SharedData<int> > in_ =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        this->getPort("intInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<int> > out_ =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        this->getPort("intOutput"));
#ifdef ENABLE_THREADING
            out_->lock();
            in_->shared_lock();
#endif
            out_ = in_;
            this->updateMTime();
#ifdef ENABLE_THREADING
            out_->unlock();
            in_->unlock();
#endif
        }

    private:

        IdentityRTC() :
                Algorithm()
        {
            ports_["intInput"] = boost::make_shared<
                    libpipe::rtc::SharedData<int> >(new int);
            ports_["intOutput"] = boost::make_shared<
                    libpipe::rtc::SharedData<int> >(new int);
        }

        /** Register Filter in the FilterFactory
         *
         */
        static const bool registered_;

        static const bool registerLoader()
        {
            std::string ids = "IdentityRTC";
            return AlgorithmFactory::instance().registerType(ids,
                IdentityRTC::create);
        }
};

const bool IdentityRTC::registered_ = registerLoader();

/** An algorithm that throws an exception during execution.
 */
class RaiseExceptionAlg : public Algorithm
{
    public:

        static Algorithm* create()
        {
            return new RaiseExceptionAlg;
        }

        ~RaiseExceptionAlg()
        {
        }
        void update(Request& req)
        {
// deliberately raise a non-libpipe exception
            throw std::exception();
        }

    private:
        RaiseExceptionAlg() :
                Algorithm()
        {
        }

        /** Register Filter in the FilterFactory
         *
         */
        static const bool registered_;

        static const bool registerLoader()
        {
            std::string ids = "RaiseExceptionAlg";
            return AlgorithmFactory::instance().registerType(ids,
                RaiseExceptionAlg::create);
        }
};

const bool RaiseExceptionAlg::registered_ = registerLoader();

}
}

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
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        void update(libpipe::Request& req)
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
#ifdef ENABLE_THREADING
            output_->lock();
            input_->shared_lock();
#endif

            LIBPIPE_PIPELINE_TRACE("UppercaseAlgorithm::update: start.");
            output_->get()->clear();
            LIBPIPE_PIPELINE_TRACE("UppercaseAlgorithm::update: transforming to uppercase.");
            std::transform(input_->get()->begin(), input_->get()->end(),
                std::back_inserter(*output_->get()), toupper);
            LIBPIPE_PIPELINE_TRACE("UppercaseAlgorithm::update: end.");
#ifdef ENABLE_THREADING
            output_->unlock();
            input_->unlock();
#endif
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
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        void update(libpipe::Request& req)
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
#ifdef ENABLE_THREADING
            output_->lock();
            input_->shared_lock();
#endif
            LIBPIPE_PIPELINE_TRACE("LowercaseAlgorithm::update: start.");
            output_.get()->get()->clear();
            LIBPIPE_PIPELINE_TRACE("LowercaseAlgorithm::update: transforming to uppercase.");
            std::transform(input_->get()->begin(), input_->get()->end(),
                std::back_inserter(*output_->get()), tolower);
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
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        void update(libpipe::Request& req)
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

#ifdef ENABLE_THREADING
            output_->lock();
            input1_->shared_lock();
            input2_->shared_lock();
#endif
            LIBPIPE_PIPELINE_TRACE("CombineAlgorithm::update: start.");
            output_.get()->get()->clear();
            LIBPIPE_PIPELINE_TRACE("CombineAlgorithm::update: combining inputs");
            combine(output_);
            LIBPIPE_PIPELINE_TRACE("CombineAlgorithm::update: end.");
#ifdef ENABLE_THREADING
            output_->unlock();
            input1_->unlock();
            input2_->unlock();
#endif
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
        }

        /** Runs the algorithm and updates the output data.
         * If the request type is DELETE the input gets deleted.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        void update(libpipe::Request& req)
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));

#ifdef ENABLE_THREADING
            output_->lock();
            input_->shared_lock();
#endif
            if (req.is(libpipe::Request::UPDATE) && this->needUpdate()) {

                LIBPIPE_PIPELINE_TRACE("ROT13Algorithm::update: start.");
                output_.get()->get()->clear();
                LIBPIPE_PIPELINE_TRACE("ROT13Algorithm::update: transforming with ROT13.");
                rot13(input_, output_);
                LIBPIPE_PIPELINE_TRACE("ROT13Algorithm::update: end.");

            } else if (req.is(libpipe::Request::DELETE)) {
                input_.reset();
                LIBPIPE_PIPELINE_TRACE("ROT13Algorithm::update: deleted the input");
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
        }

        /** Updates the output data (i.e. does nothing).
         * The output is provided as a constant, hence there is nothing to do.
         * @param[in] req The request object.
         * @return The request object.
         */
        void update(libpipe::Request& req)
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::string> > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::string> >(
                        this->getPort("StringOutput"));
            LIBPIPE_PIPELINE_TRACE("providing input.");
#ifdef ENABLE_THREADING
            output_->lock();
#endif
            (*output_->get()) = parameters_.get<std::string>("SourceString");
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

#endif
