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

#include <Philote/variable.h>

#include <data.pb.h>

/**
 * @brief Base class for all analysis discipline clients
 *
 */
class DisciplineClient
{
public:
    /**
     * @brief Construct a new Discipline Client object
     *
     */
    DisciplineClient() = default;

    /**
     * @brief Destroy the Discipline Client object
     *
     */
    ~DisciplineClient() = default;

    /**
     * @brief Get the fundamental properties of the discipline
     *
     * @return philote::DisciplineProperties
     */
    philote::DisciplineProperties GetInfo();

    /**
     * @brief Sends the stream options to the server
     *
     */
    void SendStreamOptions();

    /**
     * @brief Receives the variable definitions from the server
     *
     */
    void DefineVariables();

    /**
     * @brief Receives the partial definitions from the server
     *
     */
    void DefinePartials();

    /**
     * @brief Gets the variable meta data of the discipline
     *
     * @return philote::Variables
     */
    philote::Variables variables();

    /**
     * @brief Set the variable meta data for the discipline
     *
     * @param vars
     */
    void set_variables(const philote::Variables &vars);

private:
    //
    philote::Variables variables_; // this should be meta data
};