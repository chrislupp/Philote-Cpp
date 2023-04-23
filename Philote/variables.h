#pragma once

#include <string>
#include <map>

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
        philote::ContArray Continuous(const std::string &name) const;

        /**
         * @brief Get the continous data
         *
         * @param name
         * @return philote::ContArray
         */
        philote::DiscArray Discrete(const std::string &name) const;

        /**
         * @brief Set the continous data
         *
         * @param name
         * @param value
         */
        void SetContinuous(const std::string &name, const philote::ContArray &value);

        /**
         * @brief Set the discrete data
         *
         * @param name
         * @param value
         */
        void SetDiscrete(const std::string &name, const philote::DiscArray &value);

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