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
    UppercaseAlgorithm() : Algorithm() {}
    void addInput(const std::string& meta,
      boost::shared_ptr<FilterData> inputData) {
        input_.reset(inputData);
    }
    boost::shared_ptr<FilterData> getOutput(const std::string& meta) {
        return output_;
    }
    void run() {
        std::string& out = output_->getData();
        std::string& in = input_->getData();
        out.clear();
        std::transform(in.begin(), in.end(), std::back_inserter(out), toupper);
    }
  protected:
    typedef mstk::FilterDataWrapper<std::string> InOutType;
    boost::shared_ptr<InOutType> input_;
    boost::shared_ptr<InOutType> output_;
}

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
