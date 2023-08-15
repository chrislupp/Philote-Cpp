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

#include <string>
#include <map>
#include <utility>

#include <Philote/discipline.h>
#include <Philote/options.h>
#include <Philote/variable.h>
#include <Philote/partials.h>

#include <disciplines.grpc.pb.h>

namespace philote
{
    // forward declaration
    class ExplicitDiscipline;

    /**
     * @brief Server base class for an explicit discipline.
     *
     * This class should be inherited from by analysis discipline developers to
     * create analysis servers.
     */
    class ExplicitServer : public ExplicitService::Service
    {
    public:
        //! Constructor
        ExplicitServer() = default;

        //! Destructor
        ~ExplicitServer();

        /**
         * @brief Links the explicit server to the discipline server and
         * explicit discipline via pointers
         *
         * @param discipline
         */
        void LinkPointers(philote::DisciplineServer *discipline,
                          philote::ExplicitDiscipline *implementation);

        /**
         * @brief Dereferences all pointers
         *
         */
        void UnlinkPointers();

        /**
         * @brief RPC that computes initiates function evaluation
         *
         * @param context
         * @param stream
         * @return grpc::Status
         */
        grpc::Status ComputeFunction(grpc::ServerContext *context,
                                     grpc::ServerReaderWriter<::philote::Array,
                                                              ::philote::Array> *stream);

        /**
         * @brief RPC that computes initiates gradient evaluation
         *
         * @param context
         * @param stream
         * @return grpc::Status
         */
        grpc::Status ComputeGradient(grpc::ServerContext *context,
                                     grpc::ServerReaderWriter<::philote::Array,
                                                              ::philote::Array> *stream);

    private:
        //! Pointer to the discipline server
        philote::DisciplineServer *discipline_;

        //! Pointer to the implementation of the explicit discipline
        philote::ExplicitDiscipline *implementation_;
    };

    /**
     * @brief Explicit discipline class
     *
     * This class should be overriden by discipline developers. The basic
     * discipline and explicit discipline servers are private member variables
     * of this class and are registered to a gRPC connection together via the
     * RegisterServers member function. The discipline developer should not have
     * to interact further with these services.
     *
     */
    class ExplicitDiscipline : public Discipline
    {
    public:
        /**
         * @brief Construct a new Explicit Discipline object
         */
        ExplicitDiscipline();

        /**
         *  @brief Destroy the Explicit Disipline object
         */
        ~ExplicitDiscipline();

        /**
         * @brief Registers all services with a gRPC channel
         *
         * @param builder
         */
        void RegisterServices(grpc::ServerBuilder &builder);

        /**
         * @brief Function evaluation for the discipline.
         *
         * This function should be overridden by the developer of the
         * discipline.
         *
         * @param inputs input variables for the discipline (continuous and
         * discrete)
         * @return philote::Variables
         */
        virtual void Compute(const philote::Variables &inputs, philote::Variables &outputs);

        /**
         * @brief Gradient evaluation for the discipline.
         *
         * This function should be overridden by the developer of the
         * discipline, if applicable (not every discipline can provide
         * partials).
         *
         * @param inputs input variables for the discipline (continuous and
         * discrete)
         */
        virtual philote::Partials ComputePartials(const philote::Variables &inputs);

    private:
        //! Explicit discipline server
        philote::ExplicitServer explicit_;
    };

    /**
     * @brief Client class for calling a remote explicit discipline.
     *
     * This class may be inherited from or used by MDO framework developers.
     * However, it is a fully functional Philote MDO client.
     */
    class ExplicitClient : public DisciplineClient
    {
    public:
        //! Constructor
        ExplicitClient();

        /**
         * @brief Construct a new Explicit Client object
         *
         * @param host server host name
         */
        ExplicitClient(const std::string &host);

        //! Destructor
        ~ExplicitClient();

        /**
         * @brief Connects the client stub to a gRPC channel
         *
         * @param channel
         */
        void ConnectChannel(std::shared_ptr<grpc::ChannelInterface> channel);

        /**
         * @brief Calls the remote analysis server function evaluation via gRPC.
         *
         * Unlike the analysis server, this function does not need to be
         * overridden, as it contains all logic necessary to retrieve the remote
         * function evaluation.
         *
         * @param inputs
         */
        Variables ComputeFunction(Variables &inputs);

        /**
         * @brief Calls the remote analysis server function evaluation via gRPC.
         *
         * Unlike the analysis server, this function does not need to be
         * overridden, as it contains all logic necessary to retrieve the remote
         * gradient evaluation.
         *
         * @param inputs
         * @param partials
         */
        // void RemotePartials(std::map<std::string, ContArray> &inputs,
        //                     std::map<std::string, DiscArray> &discrete_inputs,
        //                     std::map<std::pair<std::string, std::string>, ContArray> &partials);

    private:
        //! host name of the analysis server
        std::string host_;

        std::shared_ptr<grpc::Channel> channel_;
        std::unique_ptr<ExplicitService::Stub> stub_;
    };
}