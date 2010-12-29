/*
 * testFilters.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */


#include <mstk/config.hpp>
#include <stdlib.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <mstk/Algorithm.hpp>
#include <mstk/Filter.hpp>
#include <mstk/Manager.hpp>
#include <mstk/Request.hpp>

class UppercaseAlgorithm : public mstk::Algorithm
{
  public:
    UppercaseAlgorithm() : mstk::Algorithm() {
    }

    ~UppercaseAlgorithm() {}

    mstk::Request& processRequest(mstk::Request& req) {
        if (req.is(mstk::Request::UPDATE)) {
            output_->clear();
            std::transform(input_->begin(), input_->end(), std::back_inserter(*output_), toupper);
        }
        return req;
    }

    boost::shared_ptr<std::string> getOutput() {
        return output_;
    }

    void setIncomingString(boost::shared_ptr<mstk::Filter> f, 
      boost::shared_ptr<std::string> input)  {
        // FIXME: need more info to be able to let go of 
        //this->getManager()->connect(f);
        input_ = input;
    }

  protected:
    typedef boost::shared_ptr<std::string> StringPtr;
    StringPtr input_;
    StringPtr output_;
};

class Source : public mstk::Algorithm
{
  public:
    Source(const std::string& s) : mstk::Algorithm(), output_(
      boost::make_shared<std::string>(s)) {}
    ~Source() {}
    
    boost::shared_ptr<std::string> getOutput() {
       return output_;
    }

    mstk::Request& processRequest(mstk::Request& req) {
        return req;
    }

  protected:
    boost::shared_ptr<std::string> output_;
};

class SimpleManager : public mstk::Manager
{
  public:
    ~SimpleManager() {}
    typedef std::vector<boost::shared_ptr<mstk::Filter> > FilterSet;
    mstk::Request& processRequest(Manager::AlgorithmPtr alg, mstk::Request& req) {
        typedef FilterSet::iterator FSI;
        // iterate over all sources
        for (FSI i = sources_.begin(); i != sources_.end(); ++i) {
            req = (*i)->processRequest(req);
        }
        req = alg->processRequest(req);
        return req;
    }
  protected:
    FilterSet sources_;
};

class StringFilter : public mstk::Filter
{
  public:
    StringFilter() : Filter() {
        this->setAlgorithm(boost::make_shared<UppercaseAlgorithm>());
        this->setManager(boost::make_shared<SimpleManager>());
    }
    boost::shared_ptr<UppercaseAlgorithm> getAlgorithm() {
        return this->algorithm_;
    }
};

class StringCreator : public mstk::Filter
{
  public:
    StringCreator() : mstk::Filter() {
        std::string s("Hello World!");
        this->setAlgorithm(boost::make_shared<Source>(s));
        this->setManager(boost::make_shared<SimpleManager>());
    }
};

int main(int argc, char *argv[])
{
    using namespace mstk;

    boost::shared_ptr<StringCreator> stringCreator = boost::make_shared<StringCreator>();
    boost::shared_ptr<StringFilter> stringFilter = boost::make_shared<StringFilter>();
    stringFilter->getAlgorithm()->setIncomingString(
      stringCreator->getAlgorithm()->getOutput());

    

    return EXIT_SUCCESS;
}
