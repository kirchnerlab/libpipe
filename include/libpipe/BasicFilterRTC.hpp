/*
 * BasicFilter.hpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 *
 */
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_BASICFILTERRTC_HPP__
#define __LIBPIPE_INCLUDE_LIBPIPE_BASICFILTERRTC_HPP__

#include <libpipe/config.hpp>
#include <string>
#include <libpipe/Filter.hpp>
#include <libpipe/Algorithm.hpp>
#include <libpipe/Manager.hpp>

#include <libpipe/LibpipeFactories.hpp>

namespace libpipe_rtc {


/** Wraps an algorithm and a manager into a Filter.
 * This is the preferred way of creating a filter type from given \c Algorithm
 * and Manager types. Assuming the user has implemented an algorithm in a class
 * \c UserAlgorithm and makes use of the \c normal Manager, the corresponding
 * filter is acquired using
 * \code
 * #include <libpipe/Manager.hpp>
 * ...
 * using namespace libpipe;
 * ...
 * typedef BasicFilter<UserAlgorithm, Manager> UserFilter;
 * ...
 * \endcode
 * The filter can then be used in the usual way:
 * \code
 * ...
 * boost::shared_ptr<UserFilter> uf (new UserFilter("FilterName"));
 * uf->getAlgorithm()->setParameters(...);
 * ...
 * uf->getManager()->connect(boost::dynamic_pointer_cast<Filter>(someOtherFilter->getManager()));
 * uf->getAlgorithm()->setInputFoo(someOtherFilter->getAlgorithm()->getOutputBar());
 * ...
 * \endcode
 */
class BasicFilterRTC : public libpipe::Filter
{
    public:

        static BasicFilterRTC* create(const std::string& name,
            const std::string& algorithmName, const std::string& managerName){
            return new BasicFilterRTC(name, algorithmName, managerName);
        }

        /** Destructor.
         * Virtual, to allow for subclassing.
         */
        virtual ~BasicFilterRTC();



    private:

        /** Constructor.
         * @param name The name of the filter. Passed through to libpipe::Filter.
         * @param algorithmName The name of the Algorithm that will be generated
         * @param managerName The name of the Manager that will be generated
         */

        BasicFilterRTC(const std::string& name, const std::string& algorithmName,
            const std::string& managerName);

        /** Register Filter in the FilterFactory
         *
         */
        static const bool registered_;

        static const bool registerLoader()
        {
            std::string ids = "BasicFilterRTC";
            return FilterFactory::instance().registerType(ids,
                BasicFilterRTC::create);
        }
};

const bool BasicFilterRTC::registered_ = registerLoader();

BasicFilterRTC::BasicFilterRTC(const std::string& name,
    const std::string& algorithmName, const std::string& managerName) :
        Filter(name)
{
    libpipe::Algorithm* a = libpipe_rtc::AlgorithmFactory::instance().createObject(algorithmName);
    libpipe::Manager* m = libpipe_rtc::ManagerFactory::instance().createObject(managerName);
    this->setManager(m);
    this->setAlgorithm(a);
}

BasicFilterRTC::~BasicFilterRTC()
{
}

} // namespace libpipe_rtc

#endif

