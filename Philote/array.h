#pragma once

#include <stddef.h>
#include <vector>

namespace philote
{
    /**
     * @brief Class defining an n-dimensional array.
     *
     */
    template <typename Type>
    class Array
    {
    public:
        //! Default Constructor
        Array();

        //! Default Constructor
        Array(const std::vector<size_t> &shape);

        //! Destructor
        ~Array();

        /**
         * @brief Assigns a segment of the array given a subvector
         *
         * @param start starting index of the segment
         * @param end ending index of the segment
         * @param data data to be assigned to the segment
         */
        void Segment(const size_t &start, const size_t &end,
                     const std::vector<Type> &data);

        /**
         * @brief Retrieves a reference to a segment of the array given a
         * subvector
         *
         * @param start
         * @param end
         * @return std::vector<Type>&
         */
        std::vector<Type> &Segment(const size_t &start, const size_t &end);

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

        /**
         * @brief Returns the value of the array at a given index
         *
         * @param indices indices at which the array should be accessed
         * @return double value of the array at the given indices
         */
        double operator()(const size_t &i) const;

    private:
        //! array shape
        std::vector<size_t> shape_;

        //! raw data (serialized, row major)
        std::vector<Type> data_;
    };

    /**
     * @brief Type definition for a continuous array.
     *
     */
    typedef Array<double> ContArray;

    /**
     * @brief Type definition for a discrete array.
     *
     */
    typedef Array<long> DiscArray;

} // namespace philote