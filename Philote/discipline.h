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

namespace philote
{
    class Discipline;
    /**
     * @brief Base class for all analysis discipline servers
     *
     */
    class DisciplineServer : public DisciplineService::Service
    {
    public:
        /**
         * @brief Construct a new Discipline Server object
         *
         */
        DisciplineServer() = default;

        /**
         * @brief Destroy the Discipline Server object
         *
         * Deallocates all pointers required by the discipline base class
         */
        ~DisciplineServer();

        /**
         * @brief Links all pointers needed by the discipline base class
         *
         * @param discipline
         */
        void LinkPointers(philote::Discipline *discipline);

        /**
         * @brief RPC to send the discipline properties to the client
         *
         * @param context
         * @param request
         * @param response
         * @return grpc::Status
         */
        grpc::Status GetInfo(grpc::ServerContext *context,
                             google::protobuf::Empty *request,
                             const ::philote::DisciplineProperties *response);

        /**
         * @brief RPC to define the discipline stream options to the client
         *
         * @param context
         * @param request
         * @param response
         * @return grpc::Status
         */
        grpc::Status SetStreamOptions(grpc::ServerContext *context,
                                      const ::philote::StreamOptions *request,
                                      google::protobuf::Empty *response);

        /**
         * @brief RPC to define the discipline variables on the client side
         *
         * @param context
         * @param request
         * @param writer
         * @return grpc::Status
         */
        grpc::Status GetVariableDefinitions(grpc::ServerContext *context,
                                            const google::protobuf::Empty *request,
                                            grpc::ServerWriter<::philote::VariableMetaData> *writer);

        /**
         * @brief RPC to define the discipline partials on the client side
         *
         * @param context
         * @param request
         * @param writer
         * @return grpc::Status
         */
        grpc::Status GetPartialDefinitions(grpc::ServerContext *context,
                                           const google::protobuf::Empty *request,
                                           grpc::ServerWriter<::philote::PartialsMetaData> *writer) override;

        /**
         * @brief RPC that invokes the discipline setup function
         *
         * @param context
         * @param request
         * @param response
         * @return grpc::Status
         */
        grpc::Status Setup(grpc::ServerContext *context,
                           const google::protobuf::Empty *request,
                           google::protobuf::Empty *response);

        std::vector<philote::VariableMetaData> &var_meta();

        philote::StreamOptions &stream_opts();

    private:
        //! Pointer to the discipline implementation
        philote::Discipline *discipline_;

        //! Properties of the discipline (continuity, etc.)
        philote::DisciplineProperties properties_;

        //! Options that determine how data is streamed
        StreamOptions stream_opts_;

        //! vector containing all variable metadata for the discipline
        std::vector<VariableMetaData> var_meta_;

        //! vector containing all partials metadata for the discipline
        std::vector<PartialsMetaData> partials_meta_;
    };

    /**
     * @brief Definition of the discipline base class
     *
     * This class is used as the base class for the Explicit and Implicit
     * Disciplines. It allows the discipline developers to overload the setup
     * and setup partials functions without code duplication within the explicit
     * and implicit classes.
     *
     */
    class Discipline
    {
    public:
        /**
         * @brief Construct a new Discipline object
         *
         */
        Discipline() = default;

        /**
         * @brief Destroy the Discipline object
         *
         */
        ~Discipline() = default;

        /**
         * @brief Declares an input
         *
         * @param var
         */
        void AddInput(const std::string &name,
                      const std::vector<int64_t> &shape,
                      const std::string &units);

        /**
         * @brief Declares an output
         *
         * @param var
         */
        void AddOutput(const std::string &name,
                       const std::vector<int64_t> &shape,
                       const std::string &units);

        /**
         * @brief Declare a (set of) partial(s) for the discipline
         *
         * @param f
         * @param x
         */
        void DeclarePartials(const std::string &f, const std::string &x);

        /**
         * @brief Sets up the analysis server before any function or gradient
         * evaluation.
         *
         * This function should be overridden by the developer of the
         * discipline.
         */
        virtual void Setup();

        /**
         * @brief Defines the partials for this discipline.
         *
         * This function should be overridden by the developer of the
         * discipline.
         */
        virtual void SetupPartials();

    private:
        //! Basic discipline server
        philote::DisciplineServer discipline_;
    };

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
        void GetInfo();

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
        philote::VariableMetaData GetVariableMeta(const std::string &name);

    protected:
        //! streaming options for the client/server connection
        philote::StreamOptions stream_options_;

        //! discipline properties
        philote::DisciplineProperties properties_;

        //! gRPC client stub for the generic discipline definition
        std::unique_ptr<philote::DisciplineService::Stub> stub_;

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
        void AddVariableMeta(const philote::VariableMetaData &var);
    };

}
