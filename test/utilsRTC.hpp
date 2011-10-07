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

#include <libpipe/RTC/AlgorithmRTC.hpp>
#include <libpipe/RTC/ManagerRTC.hpp>

#include <set>
#include <libpipe/Request.hpp>
#include <libpipe/RequestException.hpp>

#include <boost/shared_ptr.hpp>

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
            out_ = in_;
            this->updateMTime();
            return req;
        }
        virtual int getOutput()
        {
            return out_;
        }
        virtual void setInput(int input)
        {
            if (in_ != input) {
                in_ = input;
                this->updateMTime();
            }
        }

    private:

        IdentityRTC() :
                Algorithm(), in_(0), out_(0)
        {
        }
        int in_, out_;

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

/** Derive from Manager to be able to access the protected classes
 * for testing.
 */
class TestManager : public ManagerRTC
{
    public:
        static ManagerRTC* create()
        {
            return new TestManager;
        }

        std::set<boost::shared_ptr<Filter> > getSources()
        {
            return sources_;
        }
    private:
        TestManager(){};

        /** Register Filter in the FilterFactory
         *
         */
        static const bool registered_;

        static const bool registerLoader()
        {
            std::string ids = "TestManager";
            return ManagerFactory::instance().registerType(ids,
                TestManager::create);
        }
};

const bool TestManager::registered_ = registerLoader();
}
}

#endif
