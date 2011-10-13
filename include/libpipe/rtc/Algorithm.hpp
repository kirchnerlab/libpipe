/*
 * Algorithm.hpp
 * 
 * Copyright (c) 2010 Marc Kirchner
 *               2011 David Sichau
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_ALGORITHM_RTC_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_ALGORITHM_RTC_HPP__

#include <libpipe/config.hpp>

#include <libpipe/Request.hpp>
#include <libpipe/rtc/LibpipeDataObject.hpp>
#include <libpipe/rtc/LibpipeFactories.hpp>
#include <sys/time.h> // for timeval
#include <map>

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

/**
 * \namespace libpipe The Namespace for all libpipe classes.
 */
namespace libpipe {
/**
 * \namespace libpipe::rtc The Namespace where all classes are located which are used for the runtime configuration of libpipe
 */
namespace rtc {

/** Base class for all LIBPIPE Runtime configuration algorithms.
 */
class Algorithm
{
    public:
        /** Holds the maximum time value that can be represented in a
         * timeval struct.
         * This is mostly necessary for initialization, but also for the correct
         * behaviour of filters that act as sources.
         * @see updateMTime(), needUpdate()
         */
        static const timeval MAX_TIME;

        /** Holds the minimum time value that can be represented in a
         * timeval struct.
         * This is mostly necessary for disconnecting the input filter.
         */
        static const timeval MIN_TIME;

        /** create Methode which is registered in the Ablgorithm Factory
         * @return Pointer to the new generated Algorithm class, keep in mind to call delete on this generated pointer
         */
        static Algorithm* create();

        /** Pure virtual descructor.
         */
        virtual ~Algorithm()=0;

        /** Processes the current request object.
         * Depending on the information contained in the request object,  this will
         * call the \c update function
         * @param[inout] req A request object.
         * @return A (potentially modified) request object.
         */
        virtual Request& processRequest(Request& req);

        /** Runs the algorithm and updates the output data, if the Request
         * Type is \c Request::Update. If the request Type is \c Request::DELETE
         * after calling the update function the modification time is fixed to
         * \c Algorithm::MIN_TIME.
         * Users must overload this method (this is where the beef goes).
         * @param[in,out] req The request object (useful for logging/tracing
         *                   purposes). Also useful to get the type of request
         *                   (Update of Delete), so that the input can be deleted.
         */
        virtual Request& update(Request& req)=0;

        /** Return the last modification timestamp.
         * @return The last modification timestamp.
         */
        const timeval& getMTime() const;

        /** Set the last modification timestamp.
         * @param[in] tv Timestamp.
         */
        void setMTime(const timeval& tv);

        /** Update the modification timestamp to the current system time.
         */
        void updateMTime();

        /** Returns a flag that signifies if the Algorithm needs an update,
         * irrespective of its modification time.
         * The function essentially tests it the modification time of the algorithm
         * is equal to \c Algorithm::MAX_TIME, signifying that the algorithm needs
         * to be run and that its modification time value should be disregarded.
         * Managers must check \c needUpdate prior to making use of the information
         * delivered by \c getMTime.
         * There are two major application scenarios that make use of the flag:
         * \li When algorithms are instantiated for the first time, their creation
         *     date need not coincide with the execution sequence (this is
         *     especially true for filter setups with branches). Hence, their
         *     modification time is set to \c Algorithm::MAX_TIME to guarantee
         *     their execution on the first call to \c update.
         * \li When the precursors are deleted the modification time gets set to
         *     \c Algorithm::MIN_TIME to guarantee that the algorithm does not
         *     update himself.
         * \li Managers in filters that act as sources (i.e. do not have any
         *     predecessor) cannot determine the need for execution by comparing \c
         *     Algorithm::getMTime() against their predecessor. In the event that
         *     their internal state changes, the manager needs to call \c
         *     this->getAlgorithm()->setMTime(Algorithm::MAX_TIME), thus enforcing
         *     an update of the source and propagation along the filter chain.
         * @return Boolean flag that indicates the need for a call to the
         *         algorithm's \c update function.
         */
        bool needUpdate() const;

        /** Returns one concrete Port, to make use of it one need to
         * make dynamic pointer cast to the actual Object stored
         * \code
         * boost::dynamic_pointer_cast<libpipe::rtc::SharedData<std::string> >(
         *               this->getPorts("StringOutput"));
         * \endcode
         *
         * @param portIdentifier A \c std::string which identifies the port one wants to use
         * @return A shared_ptr to a LibpipeDataObject
         */
        boost::shared_ptr<LibpipeDataObject> getPort(std::string const& portIdentifier) const;

        /** Sets the Port to a certain LibpipeDataObject
         * @param portIdentifier A \c std::string which identifies the port one wants to set to
         * the LibpipeDataObject dataObject
         * @param dataObject The Object the Port will point to
         */
        void setInput(std::string const& portIdentifier, boost::shared_ptr<LibpipeDataObject> dataObject);

        /** Connects the port of this algorithm identified by thisPortIdentifier to the port of alg algorithm
         * identified by algPortIdentifier
         * @param alg Algorithm which port is connected to the port of this algorithm
         * @param algPortIdentifier Identifier of the port of alg
         * @param thisPortIdentifier Identifier of the port of this algorithm
         */
        void connect(Algorithm* alg, std::string const& algPortIdentifier,
            std::string const& thisPortIdentifier);

    protected:
        /** Constructor.
         */
        Algorithm();

        /** Map of the ports and their \c std::string Identifier
         */
        std::map<std::string, boost::shared_ptr<LibpipeDataObject> > ports_;

    private:

        /** Initializes the static constant \c MAX_TIME.
         * @return The maximum valid entry in a timeval struct.
         */
        static timeval initMaxTime();

        /** Initializes the static constant \c MIN_TIME.
         * @return The minimum valid entry in a timeval struct.
         */
        static timeval initMinTime();

        /** The last modification timestamp.
         */
        timeval mTime_;

};
} // namespace rtc
} // namespace libpipe

#endif
