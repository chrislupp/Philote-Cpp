/*
    Philote C++ Bindings

    Copyright 2022-2023 Christopher A. Lupp

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#pragma once

#include <map>
#include <vector>
#include <string>

namespace philote
{
    /**
     * @brief Class for saving variable metadata.
     *
     */
    class VariableMeta
    {
    public:
        /**
         * @brief Construct a new Variable Meta object
         *
         */
        VariableMeta() = default;

        /**
         * @brief Destroy the Variable Meta object
         *
         */
        ~VariableMeta() = default;

        /**
         * @brief Adds an input to the list of variables.
         *
         * @param name
         * @param shape
         * @param units
         */
        void AddInput(const std::string &name,
                      const std::vector<int64_t> &shape,
                      const std::string &units);

        /**
         * @brief Adds a discrete input to the list of variables
         *
         * @param name
         * @param shape
         * @param units
         */
        void AddDiscreteInput(const std::string &name,
                              const std::vector<int64_t> &shape,
                              const std::string &units);

        /**
         * @brief Adds an output to the list of variables
         *
         * @param name
         * @param shape
         * @param units
         */
        void AddOutput(const std::string &name,
                       const std::vector<int64_t> &shape,
                       const std::string &units);

        /**
         * @brief Adds a discrete output to the list of variables
         *
         * @param name
         * @param shape
         * @param units
         */
        void AddDiscreteOutput(const std::string &name,
                               const std::vector<int64_t> &shape,
                               const std::string &units);

        /**
         * @brief Returns the number of variables saved (including all types)
         *
         * @return size_t Number of variables in the discipline (all types).
         */
        size_t NumVariables() const;

        /**
         * @brief Returns a list of all variables saved (including all types)
         *
         * @return std::vector<std::string>
         */
        std::vector<std::string> ListVariables() const;

        /**
         * @brief Returns the type of variable for a given name.
         *
         * @param name
         * @return VariableType
         */
        const VariableType &Type(const std::string &name);

        /**
         * @brief Returns the shape of variable for a given name.
         *
         * @param name
         * @return std::vector<int64_t>
         */
        const std::vector<int64_t> &Shape(const std::string &name);

        /**
         * @brief Returns the units of variable for a given name.
         *
         * @param name
         * @return std::string
         */
        const std::string &Units(const std::string &name);

    private:
        /**
         * @brief Maps the name of the variable to its type.
         *
         */
        std::map<std::string, VariableType> type_;

        /**
         * @brief Maps the name of the variable to its shape.
         *
         */
        std::map<std::string, std::vector<int64_t>> shape_;

        /**
         * @brief Maps the name of the variable to its units.
         *
         */
        std::map<std::string, std::string> units_;

    }; // VariableMeta
} // namespace philote