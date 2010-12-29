/*
 * testFilters.cpp
 * 
 * Copyright (c) 2010 Marc Kirchner <mail@marc-kirchner.de>
 *
 */

#include <stdlib.h>

#include <mstk/config.hpp>

#include <mstk/Algorithm.hpp>
#include <mstk/FilterData.hpp>
#include <mstk/Filter.hpp>
#include <mstk/FilterType.hpp>
#include <mstk/Manager.hpp>
#include <mstk/PortInformation.hpp>

namespace mstk {

template <class T>
class FilterDataWrapper : public FilterData
{
  public:
    FilterDataWrapper() : FilterData() {}
    T& getData() { return data_; }
  protected:
    T data_;
};

} // namespace mstk

class UppercaseAlgorithm : public mstk::Algorithm
{
  public:
    UppercaseAlgorithm() : mstk::Algorithm() {
        // set the info
        PortInformation pi;
        pi.setName("in-mixed-case-string");
        pi.setType("std::string");
        this->addInputPortInformation(pi);
        pi.setName("out-uppercase-string");
        this->addOutputPortInformation(pi);
    }

    ~UppercaseAlgorithm() {}

    void* getOutputPort(const std::string& name) {
        if (name == "in-mixed-case-string") {
            return &(this->output_);
        } 
        return NULL;
    }

    void setInputPort(const std::string& lname, const Algorithm& alg, const std::string& rname) {
        if (lname == "in-mixed-case-string") {
            if (this->getInputPortInformation().find(lname) != 
              this->getInputPortInformation().end() && 
              PortInformation::is_compatible(this->getInputPortInformation[lname],
              alg.getInputPortInformation[rname])) {
                input_ = reinterpret_cast<std::string*>(alg.getOutputPort(rname));
            }
        }
    }

    void processRequest() {
        output_.clear();
        std::transform(input_->begin(), input_->end(), std::back_inserter(output_), toupper);
    }

  protected:
    std::string* input_;
    std::string output_;
};

class Source : public mstk::Algorithm
{
  public:
    Source(const std::string& s) : mstk::Algorithm(), output_(s) {}
    ~Source() {}

    void* getOutputPort(const std::string& name) {
        if (name == "out-mixed-case-string") {
            return &(this->output_);
        } 
        return NULL;
    }

    void processRequest() {
        // nothing to do
    }
  protected:
    std::string output_;
};

class SimpleManager : public mstk::Manager
{
  protected:
    std::vector<boost::shared_ptr<Filter> > sources_;

}


int main(int argc, char *argv[])
{
    using namespace mstk;

    

    return EXIT_SUCCESS;
}
