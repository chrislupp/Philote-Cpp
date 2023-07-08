#include <Philote/variables.h>

using std::map;
using std::string;
using std::vector;

using philote::ContArray;
using philote::DiscArray;
using philote::Variables;

ContArray &Variables::Continuous(const string &name)
{
    return continuous_.at(name);
}

vector<double> Variables::ContinuousSlice(const string &name,
                                          const size_t &start,
                                          const size_t &end)
{
    ContArray array = continuous_.at(name);
    vector<double> slice = array.Segment(start, end);
    return slice;
}

DiscArray &Variables::Discrete(const string &name)
{
    return discrete_.at(name);
}

vector<int64_t> Variables::DiscreteSlice(const string &name,
                                         const size_t &start,
                                         const size_t &end)
{
    DiscArray array = discrete_.at(name);
    vector<int64_t> slice = array.Segment(start, end);
    return slice;
}

void Variables::SetContinuous(const string &name, const ContArray &value)
{
    continuous_.at(name) = value;
}

void Variables::SetContinuous(const string &name,
                              const size_t &start,
                              const size_t &end,
                              const vector<double> &value)
{
    ContArray &array = continuous_.at(name);

    array.Segment(start, end, value);
}

void Variables::SetDiscrete(const string &name, const DiscArray &value)
{
    discrete_.at(name) = value;
}

void Variables::SetDiscrete(const string &name,
                            const size_t &start,
                            const size_t &end,
                            const vector<int64_t> &value)
{
    DiscArray &array = discrete_.at(name);

    array.Segment(start, end, value);
}

size_t Variables::Size()
{
    return continuous_.size() + discrete_.size();
}

size_t Variables::ContinuousSize()
{
    return continuous_.size();
}

size_t Variables::DiscreteSize()
{
    return discrete_.size();
}

std::vector<std::string> Variables::ListVariables()
{
    std::vector<std::string> names;

    // iterate through all continuous variables
    for (auto &var : continuous_)
    {
        names.push_back(var.first);
    }

    // iterate through all discrete variables
    for (auto &var : discrete_)
    {
        names.push_back(var.first);
    }

    return names;
}