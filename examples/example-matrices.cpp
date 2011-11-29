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

#include "walltime.h"

int MATRIX_SIZE = 100;

/** Matrix Multiplication
 */
class MatrixMulAlgorithm : public libpipe::rtc::Algorithm
{
    public:

        static Algorithm* create()
        {
            return new MatrixMulAlgorithm;
        }

        /** Destructor.
         */
        virtual ~MatrixMulAlgorithm()
        {
        }

        /** Runs the algorithm and updates the output data.
         * This is where all the algorithm implementation goes.
         * @param[in,out] req The request object, forwarded from \c process request.
         */
        void update(libpipe::Request& req)
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::vector<double> > > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::vector<double> > >(
                        this->getPort("MatrixOut"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::vector<double> > > input1_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::vector<double> > >(
                        this->getPort("MatrixIn1"));
            boost::shared_ptr<libpipe::rtc::SharedData<std::vector<double> > > input2_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::vector<double> > >(
                        this->getPort("MatrixIn2"));

            LIBPIPE_PIPELINE_TRACE(req, "MatrixMulAlgorithm::update: start.");
            LIBPIPE_PIPELINE_TRACE(req,
                "MatrixMulAlgorithm::update: multiplication of two matrices.");
#ifdef ENABLE_THREADING
            output_->lock();
            input1_->shared_lock();
            input2_->shared_lock();
#endif
            std::vector<double>* tempIn1 = input1_->get();
            std::vector<double>* tempIn2 = input2_->get();
            std::vector<double>* tempOut = output_->get();
            for (int i = 0; i < MATRIX_SIZE; i++) {
                for (int j = 0; j < MATRIX_SIZE; j++) {
                    double sum = 0;
                    for (int k = 0; k < MATRIX_SIZE; k++) {
                        sum += (*tempIn1)[i * MATRIX_SIZE + k]
                                * (*tempIn2)[k * MATRIX_SIZE + j];
                    }
                    (*tempOut)[i * MATRIX_SIZE + j] = sum / MATRIX_SIZE;
                }
            }
#ifdef ENABLE_THREADING
            output_->unlock();
            input1_->unlock();
            input2_->unlock();
#endif
            LIBPIPE_PIPELINE_TRACE(req, "MatrixMulAlgorithm::update: end.");
        }

    protected:
        /** Constructor.
         * Make sure to call the \c libpipe::rtc::Algorithm constructor.
         */
        MatrixMulAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["MatrixIn1"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::vector<double> > >();
            ports_["MatrixIn2"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::vector<double> > >();
            ports_["MatrixOut"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::vector<double> > >(
                new std::vector<double>(MATRIX_SIZE * MATRIX_SIZE));
        }

    private:

        /** registers the Algorithm in the factory
         * @return true is registration was successful
         */
        static const bool registerLoader()
        {
            std::string ids = "MatrixMulAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                MatrixMulAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;

};

const bool MatrixMulAlgorithm::registered_ = registerLoader();

/** Provides a constant matrix as output.
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
         */
        void update(libpipe::Request& req)
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::vector<double> > > output_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::vector<double> > >(
                        this->getPort("MatrixOut"));

            LIBPIPE_PIPELINE_TRACE(req, "providing input.");
#ifdef ENABLE_THREADING
            output_->lock();
#endif
            // fill matrix with some values
            std::vector<double>* tempOut = output_->get();
            for (int row = 0; row < MATRIX_SIZE; row++) {
                for (int col = 0; col < MATRIX_SIZE; col++) {
                    (*tempOut)[col + (row * MATRIX_SIZE)] = col + row;
                }
            }
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
            ports_["MatrixOut"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::vector<double> > >(
                new std::vector<double>(MATRIX_SIZE * MATRIX_SIZE));
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

/** Prints the Matrix
 */
class Printer : public libpipe::rtc::Algorithm
{
    public:
        static Algorithm* create()
        {
            return new Printer;
        }

        /** Destructor.
         */
        virtual ~Printer()
        {
        }

        /** Updates the output data (i.e. does nothing).
         * The output is provided as a constant, hence there is nothing to do.
         * @param[in] req The request object.
         */
        void update(libpipe::Request& req)
        {
            boost::shared_ptr<libpipe::rtc::SharedData<std::vector<double> > > input_ =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<std::vector<double> > >(
                        this->getPort("MatrixIn"));

            LIBPIPE_PIPELINE_TRACE(req, "printing matrix");
#ifdef ENABLE_THREADING
            input_->shared_lock();
#endif
            // print the matrix
            for (int row = 0; row < MATRIX_SIZE; row++) {
                for (int col = 0; col < MATRIX_SIZE; col++) {
                    std::cout << input_->get()->at(col + (row * MATRIX_SIZE))
                            << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            std::cout << std::endl;
#ifdef ENABLE_THREADING
            input_->unlock();
#endif

        }

    protected:

    private:
        /** Constructor.
         */
        Printer() :
                libpipe::rtc::Algorithm()
        {
            ports_["MatrixIn"] = boost::make_shared<
                    libpipe::rtc::SharedData<std::vector<double> > >();
        }
        /** registers the Algorithm in the factory
         * @return true is registration was successful
         */
        static const bool registerLoader()
        {
            std::string ids = "Printer";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                Printer::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;

};

const bool Printer::registered_ = registerLoader();

/** Handles the several Algorithm so that they can be executed in parallel,
 *  as the Pipeline will execute them in sequential order.
 */
class Handler : public libpipe::rtc::Algorithm
{
    public:
        static Algorithm* create()
        {
            return new Handler;
        }

        /** Destructor.
         */
        virtual ~Handler()
        {
        }

        /** Does nothing.
         * The output is provided as a constant, hence there is nothing to do.
         * @param[in] req The request object.
         */
        void update(libpipe::Request& req)
        {
            LIBPIPE_PIPELINE_TRACE(req, "start handler");
        }

    protected:

    private:
        /** Constructor.
         */
        Handler() :
                libpipe::rtc::Algorithm()
        {
        }
        /** registers the Algorithm in the factory
         * @return true is registration was successful
         */
        static const bool registerLoader()
        {
            std::string ids = "Handler";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                Handler::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;

};

const bool Handler::registered_ = registerLoader();

int main(int argc, char *argv[])
{
    using namespace libpipe::rtc;
    if (argc == 2) {
        MATRIX_SIZE = atoi(argv[1]);
    }
    else{
        std::cerr<<"usage: ./example-matrices MATRIX_SIZE[int]"<<std::endl;
        exit(1);
    }

    std::cout << "Matrix Size: " << MATRIX_SIZE << std::endl;

    std::map<std::string, std::string> inputFiles;
    inputFiles["FilterInput"] = "inputFileFilterJSONMatrix.txt";
    inputFiles["ConnectionInput"] = "inputFileConnectionJSONMatrix.txt";
    inputFiles["PipelineInput"] = "inputFilePipelineJSONMatrix.txt";
    inputFiles["ParameterInput"] = "inputFileParametersJSONMatrix.txt";

    Pipeline pipeline;
    try {
        PipelineLoader loader(inputFiles);
        pipeline = loader.getPipeline();
    } catch (libpipe::utilities::Exception& e) {
        std::cerr << e.what() << std::endl;
    }

    double time, time_start = 0.0;

    time = walltime(&time_start);

    try {
        pipeline.run();
    } catch (libpipe::utilities::Exception& e) {
        std::cerr << e.what() << std::endl;
    }

    time = walltime(&time);

    std::cout << time << " sec" << std::endl;

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

