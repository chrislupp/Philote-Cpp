
#include <Philote/variables.h>

using std::map;
using std::string;

using philote::ContArray;
using philote::DiscArray;
using philote::Variables;

ContArray Variables::Continuous(const string &name) const
{
    return continuous_.at(name);
}

DiscArray Variables::Discrete(const string &name) const
{
    return discrete_.at(name);
}

void Variables::SetContinuous(const string &name, const ContArray &value)
{
    continuous_[name] = value;
}

void Variables::SetDiscrete(const string &name, const DiscArray &value)
{
    discrete_[name] = value;
}