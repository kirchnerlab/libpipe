/*
 * utils.hpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 * Helper classes for test case development.
 *
 */
#ifndef __LIBPIPE_TEST_UTILS_HPP__
#define __LIBPIPE_TEST_UTILS_HPP__

#include <libpipe/rtc/AlgorithmRTC.hpp>
#include <libpipe/rtc/ManagerRTC.hpp>
#include <libpipe/rtc/SharedDataRTC.hpp>

#include <set>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include <sstream>

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
        Request& update(Request& req)
        {
            LIBPIPE_REQUEST_TRACE(req, "Identity: copying value.");

            boost::shared_ptr<libpipe::rtc::SharedData<int> > in_ =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        this->getPort("intInput"));
            boost::shared_ptr<libpipe::rtc::SharedData<int> > out_ =
                    boost::dynamic_pointer_cast<libpipe::rtc::SharedData<int> >(
                        this->getPort("intOutput"));
            out_ = in_;
            this->updateMTime();
            return req;
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
        Request& update(Request& req)
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

#endif
