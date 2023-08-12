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
#include <grpcpp/grpcpp.h>

#include <Philote/variable.h>
#include <Philote/discipline_client.h>

#include <disciplines.grpc.pb.h>

namespace philote
{
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
         * @brief Calls the remote analysis server function evaluation via gRPC.
         *
         * Unlike the analysis server, this function does not need to be
         * overridden, as it contains all logic necessary to retrieve the remote
         * function evaluation.
         *
         * @param inputs
         * @param discrete_inputs
         * @param outputs
         * @param discrete_outputs
         */
        void ComputeFunction(Variables &inputs, Variables &outputs);

        /**
         * @brief Calls the remote analysis server function evaluation via gRPC.
         *
         * Unlike the analysis server, this function does not need to be
         * overridden, as it contains all logic necessary to retrieve the remote
         * gradient evaluation.
         *
         * @param inputs
         * @param discrete_inputs
         * @param partials
         */
        // void RemotePartials(std::map<std::string, ContArray> &inputs,
        //                     std::map<std::string, DiscArray> &discrete_inputs,
        //                     std::map<std::pair<std::string, std::string>, ContArray> &partials);

    private:
        //! host name of the analysis server
        std::string host_;

        std::shared_ptr<grpc::Channel> channel_;
        std::unique_ptr<ExplicitDiscipline::Stub> stub_;
    };
} // namespace philote