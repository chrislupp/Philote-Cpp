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
#include <vector>
#include <Philote/explicit_server.h>

using std::string;
using std::vector;

using google::protobuf::Empty;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using philote::DisciplineServer;

void DisciplineServer::AddVariable(const ::philote::VariableMetaData &var)
{
    var_meta_.push_back(var);
}

void DisciplineServer::DeclarePartials(const std::string &f, const std::string &x)
{
}

Status DisciplineServer::SetStreamOptions(ServerContext *context,
                                          const ::philote::StreamOptions *request,
                                          Empty *response)
{
    stream_opts_ = *request;

    return Status::OK;
}

Status DisciplineServer::DefineVariables(ServerContext *context,
                                         const Empty *request,
                                         ServerWriter<::philote::VariableMetaData> *writer)
{
    VariableMetaData meta;

    for (const VariableMetaData &var : var_meta_)
        writer->Write(var);

    return Status::OK;
}

Status DisciplineServer::DefinePartials(ServerContext *context,
                                        const Empty *request,
                                        ServerWriter<::philote::PartialsMetaData> *writer)
{
    for (const PartialsMetaData &partial : partials_meta_)
        writer->Write(partial);

    return Status::OK;
}