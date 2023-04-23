
#include <Philote/variables.h>

using std::map;
using std::string;

using namespace philote;

ContArray Variables::Continuous(const string &name) const
{
    return ContArray();
}

DiscArray Variables::Discrete(const string &name) const
{
    return DiscArray();
}

void Variables::SetContinuous(const string &name, const ContArray &value)
{
}

void Variables::SetDiscrete(const string &name, const DiscArray &value)
{
}