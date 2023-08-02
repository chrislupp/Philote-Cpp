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
#include <vector>

#include <disciplines.grpc.pb.h>

namespace philote
{
    /**
     * @brief Base class for all analysis discipline servers
     *
     */
    class DisciplineServer : public Discipline::Service
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
         */
        ~DisciplineServer() = default;

        /**
         * @brief Declares a variable
         *
         * @param var
         */
        void AddVariable(const ::philote::VariableMetaData &var);

        /**
         * @brief Declare a (set of) partial(s) for the discipline
         *
         * @param f
         * @param x
         */
        void DeclarePartials(const std::string &f, const std::string &x);

        /**
         * @brief RPC to define the discipline stream options to the client.
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
         * @brief RPC to define the discipline variables on the client side.
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
         * @brief RPC to define the discipline partials on the client side.
         *
         * @param context
         * @param request
         * @param writer
         * @return grpc::Status
         */
        grpc::Status GetPartialDefinitions(grpc::ServerContext *context,
                                           const google::protobuf::Empty *request,
                                           grpc::ServerWriter<::philote::PartialsMetaData> *writer) override;

    protected:
        //! Options that determine how data is streamed
        StreamOptions stream_opts_;

        //! vector containing all variable metadata for the discipline
        std::vector<VariableMetaData> var_meta_;

        //! vector containing all partials metadata for the discipline
        std::vector<PartialsMetaData> partials_meta_;
    };
} // namespace philote
