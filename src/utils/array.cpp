
#include <cstdarg>
#include <stdexcept>
#include <Philote/array.h>

#include <iostream>

using namespace philote;

// explicit instantiation
template class Array<TYPE>;

template <>
Array<TYPE>::Array() {}

template <>
Array<TYPE>::Array(const std::vector<size_t> &shape)
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

template <>
Array<TYPE>::~Array() {}

template <>
void Array<TYPE>::Segment(const size_t &start, const size_t &end,
                          const std::vector<TYPE> &data)
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

template <>
std::vector<TYPE> &Array<TYPE>::Segment(const size_t &start, const size_t &end)
{
    std::vector<TYPE> data(end - start + 1);

    // check that the segment matches length of (end - start)
    if ((end - start) + 1 != data_.size())
    {
        std::string expected = std::to_string((end - start) + 1);
        std::string actual = std::to_string(data.size());
        throw std::length_error("Vector data has incompatable length. Should be " +
                                expected + ", but received " + actual + ".");
    }

    // assign the segment
    for (size_t i = 0; i < (end - start) + 1; i++)
        data[i] = data_[start + i];

    return data;
}

template <>
std::vector<size_t> Array<TYPE>::Shape() const
{
    return shape_;
}

template <>
size_t Array<TYPE>::Size() const
{
    return data_.size();
}

template <>
double Array<TYPE>::operator()(const size_t &i) const
{
    return data_[i];
}
