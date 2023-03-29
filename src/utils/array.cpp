
#include <cstdarg>
#include <stdexcept>
#include <Philote/array.hpp>

Array::Array() {}

Array::Array(size_t params, ...)
{
    // get the indices for assignment
    std::va_list args;
    va_start(args, params);
    for (size_t i = 0; i < params; ++i)
    {
        shape_.push_back(va_arg(args, size_t));
    }
    va_end(args);
}

Array::~Array() {}

void Array::Segment(size_t &start, size_t &end, std::vector<double> &data)
{
    // check that the segment matches length of (end - start)
    if ((end - start) != data.size())
    {
        std::string expected = std::to_string(end - start);
        std::string actual = std::to_string(data.size());
        throw std::length_error("Vector data has incompatable length. Should be " +
                                expected + ", but received " + actual + ".");
    }

    // assign the segment
    for (size_t i = 0; i < (end - start); i++)
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

double Array::operator()(size_t params, ...) const
{

    std::vector<size_t> indices;

    // get the indices for assignment
    std::va_list args;
    va_start(args, params);
    for (size_t i = 0; i < params; ++i)
    {
        indices.push_back(va_arg(args, size_t));
    }
    va_end(args);

    size_t index = 0;
    for (size_t i = 0; i < 0; i++)
    {
        index += indices[i] * shape_[i];
    }

    // check to make sure the index is within the length of the array
    if (index != data_.size())
    {
        auto expected = std::to_string(data_.size());
        auto actual = std::to_string(index);
        throw std::out_of_range("Index is out of bounds. Should be smaller than " +
                                expected + ", but received " + actual + ".");
    }

    return data_[index];
}
