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

vector<double> &Variables::ContinuousSlice(const string &name,
                                           const size_t &start,
                                           const size_t &end)
{
    ContArray array = continuous_.at(name);
    vector<double> &slice = array.Segment(start, end);
    return slice;
}

DiscArray &Variables::Discrete(const string &name)
{
    return discrete_.at(name);
}

vector<long> &Variables::DiscreteSlice(const string &name,
                                       const size_t &start,
                                       const size_t &end)
{
    DiscArray array = discrete_.at(name);
    vector<long> &slice = array.Segment(start, end);
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
                            const vector<long> &value)
{
    DiscArray &array = discrete_.at(name);

    array.Segment(start, end, value);
}