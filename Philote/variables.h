#pragma once

#include <string>
#include <map>
#include <vector>
#include <Philote/array.h>
#include <Philote/variables.h>

namespace philote
{
    /**
     * @brief A class for storing continuous and discrete variables
     *
     */
    class Variables
    {
    public:
        /**
         * @brief Construct a new Variables object
         *
         */
        Variables() = default;

        /**
         * @brief Destroy the Variables object
         *
         */
        ~Variables() = default;

        /**
         * @brief Get the continous data
         *
         * @param name
         * @return philote::ContArray
         */
        philote::ContArray &Continuous(const std::string &name);

        /**
         * @brief Get a continous data slice
         *
         * @param name
         * @param start
         * @param end
         * @return std::vector<double>
         */
        std::vector<double> ContinuousSlice(const std::string &name,
                                            const size_t &start,
                                            const size_t &end);

        /**
         * @brief Get the discrete data
         *
         * @param name
         * @return philote::DiscArray
         */
        philote::DiscArray &Discrete(const std::string &name);

        /**
         * @brief Get a discrete data slice
         *
         * @param name
         * @param start
         * @param end
         * @return std::vector<double>
         */
        std::vector<int64_t> DiscreteSlice(const std::string &name,
                                           const size_t &start,
                                           const size_t &end);

        /**
         * @brief Set the continous data
         *
         * @param name
         * @param value
         */
        void SetContinuous(const std::string &name, const philote::ContArray &value);

        /**
         * @brief Set the continuous data from an array slice
         *
         * @param name
         * @param start
         * @param end
         * @param value
         */
        void SetContinuous(const std::string &name,
                           const size_t &start,
                           const size_t &end,
                           const std::vector<double> &value);

        /**
         * @brief Set the discrete data
         *
         * @param name
         * @param value
         */
        void SetDiscrete(const std::string &name, const philote::DiscArray &value);

        /**
         * @brief Set the discrete data from an array slice
         *
         * @param name
         * @param start
         * @param end
         * @param value
         */
        void SetDiscrete(const std::string &name,
                         const size_t &start,
                         const size_t &end,
                         const std::vector<int64_t> &value);

        /**
         * @brief Returns the number of all variables stored
         *
         * @return size_t
         */
        size_t Size();

        /**
         * @brief Returns the number of continuous variables stored
         *
         * @return size_t
         */
        size_t ContinuousSize();

        /**
         * @brief Returns the number of discrete variables stored
         *
         * @return size_t
         */
        size_t DiscreteSize();

        /**
         * @brief Lists names of all variables stored
         *
         * @return std::vector<std::string>
         */
        std::vector<std::string> ListVariables();

    private:
        /**
         * @brief Map of the continuous variables
         *
         */
        std::map<std::string, philote::ContArray> continuous_;

        /**
         * @brief Map of the discrete variables
         *
         */
        std::map<std::string, philote::DiscArray> discrete_;
    };
}