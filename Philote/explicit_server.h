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
#include <Philote/options.h>
#include <Philote/variable.h>
#include <Philote/partials.h>
#include <Philote/discipline_server.h>

#include <disciplines.grpc.pb.h>

namespace philote
{
    /**
     * @brief Server base class for an explicit discipline.
     *
     * This class should be inherited from by analysis discipline developers to
     * create analysis servers.
     */
    class ExplicitServer : public ExplicitDiscipline::Service,
                           public philote::DisciplineServer
    {
    public:
        //! Constructor
        ExplicitServer() = default;

        //! Destructor
        ~ExplicitServer() = default;

        grpc::Status Functions(grpc::ServerContext *context,
                               grpc::ServerReaderWriter<::philote::Array,
                                                        ::philote::Array> *stream);

        grpc::Status Gradient(grpc::ServerContext *context,
                              grpc::ServerReaderWriter<::philote::Array,
                                                       ::philote::Array> *stream);

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
        virtual philote::Variables Compute(const philote::Variables &inputs);

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
    };
} // namespace philote