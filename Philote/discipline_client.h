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
#include <disciplines.grpc.pb.h>

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
    DisciplineClient();

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
     * @brief Sends the options for the discipline
     *
     */
    void SendOptions();

    /**
     * @brief Sets up the discipline
     *
     */
    void Setup();

    /**
     * @brief Receives the variable definitions from the server
     *
     */
    void GetVariableDefinitions();

    /**
     * @brief Receives the partial definitions from the server
     *
     */
    void GetPartialDefinitions();

    /**
     * @brief Get the names of all variables associated with this discipline
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> GetVariableNames();

    /**
     * @brief Gets the variable meta data of the discipline
     *
     * @return philote::Variables
     */
    philote::VariableMetaData GetVariable(const std::string &name);

private:
    //! streaming options for the client/server connection
    philote::StreamOptions options_;

    //! gRPC client stub for the generic discipline definition
    std::unique_ptr<philote::Discipline::Stub> stub_;

    //! variable meta data
    std::vector<philote::VariableMetaData> var_meta_;

    /**
     * @brief Set the variable meta data for the discipline
     *
     * This function must be private to prevent a user from accidentally adding
     * variables to the discipline client. It should only get called by the
     * object itself and only in the context of a remote procedure call.
     *
     * @param vars
     */
    void AddVariable(const philote::VariableMetaData &var);
};