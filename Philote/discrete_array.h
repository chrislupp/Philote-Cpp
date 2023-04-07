#pragma once

#include <stddef.h>
#include <vector>

namespace philote
{
    /**
     * @brief Class defining an n-dimensional array of continuous data (double).
     *
     */
    class DiscreteArray
    {
    public:
        //! Constructor
        DiscreteArray();

        //! Destructor
        ~DiscreteArray();

        //! Accessor
        long operator()(size_t params, ...);

    private:
        //! array shape
        std::vector<size_t> shape_;

        //! raw data (serialized, row major)
        std::vector<long> data_;
    };
} // namespace philote