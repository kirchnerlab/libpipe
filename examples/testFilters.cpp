/*
 * testFilters.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */


#include <mstk/config.hpp>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <mstk/Algorithm.hpp>
#include <mstk/Filter.hpp>
#include <mstk/Manager.hpp>
#include <mstk/Request.hpp>


class TeeAlgorithm : public mstk::Algorithm
{
  public:
    TeeAlgorithm() : mstk::Algorithm(), 
      output1_(),
      output2_() {
    }

    ~TeeAlgorithm() {}

    mstk::Request& processRequest(mstk::Request& req) {
        if (req.is(mstk::Request::UPDATE)) {
            output2_ = output1_ = *input_;
        }
        return req;
    }

    std::string* getOutput1() {
        return &output1_;
    }

    std::string* getOutput2() {
        return &output2_;
    }

    void setIncomingString(boost::shared_ptr<std::string> input)  {
        input_ = input;
    }

  protected:
    typedef boost::shared_ptr<std::string> StringPtr;
    StringPtr input_;
    std::string output1_, output2_;
};

class UppercaseAlgorithm : public mstk::Algorithm
{
  public:
    UppercaseAlgorithm() : mstk::Algorithm(), output_(boost::make_shared<std::string>()) {
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

    void setIncomingString(boost::shared_ptr<std::string> input)  {
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
    typedef std::set<Manager*> ManagerSet;

    ~SimpleManager() {}

    void setAlgorithm(mstk::Algorithm* alg) {
        algorithm_ = alg;
    }

    mstk::Request& processRequest(mstk::Request& req) {
        typedef ManagerSet::iterator MSI;
        // iterate over all sources
        for (MSI i = sources_.begin(); i != sources_.end(); ++i) {
            req = (*i)->processRequest(req);
        }
        req = algorithm_->processRequest(req);
        return req;
    }

    void connect(SimpleManager* sm) {
        sources_.insert(sm);
    }

  protected:
    ManagerSet sources_;
    mstk::Algorithm* algorithm_;
};

class StringFilter : public mstk::Filter
{
  public:
    StringFilter() : Filter() {
        this->setAlgorithm(new UppercaseAlgorithm);
        SimpleManager* sm = new SimpleManager;
        sm->setAlgorithm(this->getAlgorithm());
        this->setManager(sm);
    }
    UppercaseAlgorithm* getAlgorithm() {
        return dynamic_cast<UppercaseAlgorithm*>(this->algorithm_);
    }
    SimpleManager* getManager() {
        return dynamic_cast<SimpleManager*>(this->manager_);
    }
};

class StringTeeFilter : public mstk::Filter
{
  public:
    StringTeeFilter() : Filter() {
        this->setAlgorithm(new TeeAlgorithm);
        SimpleManager* sm = new SimpleManager;
        sm->setAlgorithm(this->getAlgorithm());
        this->setManager(sm);
    }
    TeeAlgorithm* getAlgorithm() {
        return dynamic_cast<TeeAlgorithm*>(this->algorithm_);
    }
    SimpleManager* getManager() {
        return dynamic_cast<SimpleManager*>(this->manager_);
    }
};

class StringCreator : public mstk::Filter
{
  public:
    StringCreator() : mstk::Filter() {
        std::string s("Hello World!");
        this->setAlgorithm(new Source(s));
        SimpleManager* sm = new SimpleManager;
        sm->setAlgorithm(this->getAlgorithm());
        this->setManager(sm);
    }
    Source* getAlgorithm() {
        return dynamic_cast<Source*>(this->algorithm_);
    }
    SimpleManager* getManager() {
        return dynamic_cast<SimpleManager*>(this->manager_);
    }
};

int main(int argc, char *argv[])
{
    using namespace mstk;

    StringCreator* stringCreator = new StringCreator;
    StringFilter* stringFilter = new StringFilter;
    StringTeeFilter* stringTeeFilter = new StringTeeFilter;

    stringFilter->getManager()->connect(stringCreator->getManager());
    stringFilter->getAlgorithm()->setIncomingString(
      stringCreator->getAlgorithm()->getOutput());

    stringTeeFilter->getManager()->connect(stringFilter->getManager());
    stringTeeFilter->getAlgorithm()->setIncomingString(
      stringFilter->getAlgorithm()->getOutput());

    Request req(mstk::Request::UPDATE);
    stringTeeFilter->getManager()->processRequest(req);
    
    std::cout << "StringCreator out: " << *(stringCreator->getAlgorithm()->getOutput()) << '\n';
    std::cout << "StringFilter out: " << *(stringFilter->getAlgorithm()->getOutput()) << std::endl;
    std::cout << "StringTeeFilter out: " << *(stringTeeFilter->getAlgorithm()->getOutput1()) << ", "
      << *(stringTeeFilter->getAlgorithm()->getOutput2()) << std::endl;
    delete stringTeeFilter;
    delete stringFilter;
    delete stringCreator;

    

    return EXIT_SUCCESS;
}
