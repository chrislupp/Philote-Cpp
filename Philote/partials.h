#pragma once

#include <map>
#include <string>

#include <Philote/array.h>

namespace philote
{
    /**
     * @brief A class for storing partials data
     *
     */
    class Partials
    {
    public:
        /**
         * @brief Construct a new Partials object
         *
         */
        Partials() = default;

        /**
         * @brief Destroy the Partials object
         *
         */
        ~Partials() = default;

        philote::ContArray J(const std::string &func, const std::string &var) const;

        void SetJ(const std::string &func, const std::string &var,
                  const philote::ContArray &value);

    private:
        std::map<std::string, std::map<std::string, philote::ContArray>> data_;
    };
}