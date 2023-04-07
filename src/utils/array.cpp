
#include <cstdarg>
#include <stdexcept>
#include <Philote/array.h>

#include <iostream>

using namespace philote;

Array::Array() {}

Array::Array(const std::vector<size_t> &shape)
{
    // assign the array shape
    shape_ = shape;

    // serialized array size
    size_t size = 1;
    for (size_t i = 0; i < shape_.size(); i++)
        size *= shape_[i];

    // initialize the array from the shape input
    data_.resize(size);
}

Array::~Array() {}

void Array::Segment(const size_t &start, const size_t &end,
                    const std::vector<double> &data)
{
    // check that the segment matches length of (end - start)
    if ((end - start) + 1 != data.size())
    {
        std::string expected = std::to_string((end - start) + 1);
        std::string actual = std::to_string(data.size());
        throw std::length_error("Vector data has incompatable length. Should be " +
                                expected + ", but received " + actual + ".");
    }

    // assign the segment
    for (size_t i = 0; i < (end - start) + 1; i++)
        data_[start + i] = data[i];
}

std::vector<size_t> Array::Shape() const
{
    return shape_;
}

size_t Array::Size() const
{
    return data_.size();
}

double Array::operator()(const size_t &i) const
{
    return data_[i];
}
