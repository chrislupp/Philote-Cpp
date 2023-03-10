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
    //! Constructor
    Array();

    //! Destructor
    ~Array();

    //! Accessor
    double operator()(size_t params, ...);

private:
    //! array shape
    std::vector<size_t> shape_;

    //! raw data (serialized, row major)
    std::vector<double> data_;
};