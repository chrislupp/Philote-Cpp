
#include <cstdarg>
#include <Philote/discrete_array.h>

using namespace philote;

DiscreteArray::DiscreteArray() {}

DiscreteArray::~DiscreteArray() {}

long DiscreteArray::operator()(size_t params, ...)
{
    int index = 0;
    std::va_list args;
    va_start(args, params);
    for (size_t i = 0; i < params; ++i)
    {
        index += va_arg(args, size_t);
    }
    va_end(args);

    return data_[index];
}