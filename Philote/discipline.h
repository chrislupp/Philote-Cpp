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

    This work has been cleared for public release, distribution unlimited, case
    number: AFRL-2023-5716.

    The views expressed are those of the authors and do not reflect the
    official guidance or position of the United States Government, the
    Department of Defense or of the United States Air Force.

    Statement from DoD: The Appearance of external hyperlinks does not
    constitute endorsement by the United States Department of Defense (DoD) of
    the linked websites, of the information, products, or services contained
    therein. The DoD does not exercise any editorial, security, or other
    control over the information you may find at these locations.
*/
#pragma once

#include "google/protobuf/struct.pb.h"

#include <Philote/variable.h>

#include <data.pb.h>
#include <disciplines.grpc.pb.h>

namespace philote
{
    // forward declaration
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
        ~DisciplineServer() override;

        /**
         * @brief Links all pointers needed by the discipline base class
         *
         * @param discipline
         */
        void LinkPointers(philote::Discipline *discipline);

        /**
         * @brief Unlinks all pointers
         */
        void UnlinkPointers();

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
                                      google::protobuf::Empty *response) override;

        /**
         * @brief Set the discipline options
         *
         * @param context
         * @param request
         * @param response
         * @return grpc::Status
         */
        grpc::Status SetOptions(grpc::ServerContext *context,
                                const ::philote::DisciplineOptions *request,
                                google::protobuf::Empty *response) override;

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
                                            grpc::ServerWriter<::philote::VariableMetaData> *writer) override;

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
                           google::protobuf::Empty *response) override;

    private:
        //! Pointer to the discipline implementation
        philote::Discipline *discipline_;
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
        Discipline();

        /**
         * @brief Destroy the Discipline object
         *
         */
        ~Discipline() = default;

        /**
         * @brief Accesses the variable meta data
         */
        std::vector<philote::VariableMetaData> &var_meta();

        /**
         * @brief Accesses the partials meta data
         */
        std::vector<philote::PartialsMetaData> &partials_meta();

        /**
         * @brief Gets the discipline properties
         *
         * @return DisciplineProperties
         */
        philote::DisciplineProperties &properties();

        /**
         * @brief Gets the stream options
         *
         * @return StreamOptions&
         */
        philote::StreamOptions &stream_opts();

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
         * @brief Sets up all discipline options based on a protobuf struct that
         * the server received from the client.
         *
         * @param options_struct
         */
        virtual void Initialize(const google::protobuf::Struct &options_struct);

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

    protected:
        //! Properties of the discipline (continuity, etc.)
        philote::DisciplineProperties properties_;

        //! Options that determine how data is streamed
        StreamOptions stream_opts_;

        //! vector containing all variable metadata for the discipline
        std::vector<VariableMetaData> var_meta_;

        //! vector containing all partials metadata for the discipline
        std::vector<PartialsMetaData> partials_meta_;

        //! Basic discipline server
        philote::DisciplineServer discipline_server_;
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
         * @brief Connects the client stub to a gRPC channel
         *
         * @param channel
         */
        void ConnectChannel(const std::shared_ptr<grpc::ChannelInterface> &channel);

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
        void SendOptions(const philote::DisciplineOptions &options);

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

        /**
         * @brief Gets the partials meta data
         *
         * @return std::vector<philote::PartialsMetaData>
         */
        std::vector<philote::PartialsMetaData> partials_meta();

    protected:
        //! streaming options for the client/server connection
        philote::StreamOptions stream_options_;

        //! discipline properties
        philote::DisciplineProperties properties_;

        //! gRPC client stub for the generic discipline definition
        std::unique_ptr<philote::DisciplineService::Stub> stub_;

        //! variable meta data
        std::vector<philote::VariableMetaData> var_meta_;

        //! vector containing all partials metadata for the discipline
        std::vector<philote::PartialsMetaData> partials_meta_;
    };

}
