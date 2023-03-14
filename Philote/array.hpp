#pragma once

#include <stddef.h>
#include <vector>

/**
 * @brief Class defining an n-dimensional array of continuous data (double).
 *
 */
class Array
{
public:
    //! Default Constructor
    Array();

    //! Default Constructor
    Array(size_t params, ...);

    //! Destructor
    ~Array();

    /**
     * @brief Assigns a segment of the array given a subvector
     *
     * @param start starting index of the segment
     * @param end ending index of the segment
     * @param data data to be assigned to the segment
     */
    void Segment(size_t &start, size_t &end, std::vector<double> &data);

    /**
     * @brief Returns the shape of the array
     *
     * @return std::vector<size_t> vector containing the length of the
     * individual dimensions
     */
    std::vector<size_t> Shape() const;

    /**
     * @brief Returns the size of the array.
     *
     * @return size_t size of the array
     */
    size_t Size() const;

    //! Accessor
    /**
     * @brief Returns the value of the array at a given index
     *
     * @param params indices
     * @param ...
     * @return double value of the array at the given indices
     */
    double operator()(size_t params, ...) const;

private:
    //! array shape
    std::vector<size_t> shape_;

    //! raw data (serialized, row major)
    std::vector<double> data_;
};