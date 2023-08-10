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

using google::protobuf::Empty;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using philote::DisciplineServer;
using std::string;
using std::vector;

void DisciplineServer::AddVariable(const string &name,
                                   const vector<int64_t> &shape,
                                   const string &units)
{
    VariableMetaData var;
    var.set_name(name);
    for (const int64_t dim : shape)
        var.add_shape(dim);
    var.set_units(units);

    var_meta_.push_back(var);
}

void DisciplineServer::DeclarePartials(const string &f, const string &x)
{
    PartialsMetaData meta;
    meta.set_name(f);
    meta.set_subname(x);

    partials_meta_.push_back(meta);
}

grpc::Status DisciplineServer::GetInfo(ServerContext *context,
                                       Empty *request,
                                       const DisciplineProperties *response)
{
    response = &properties_;

    return Status::OK;
}

Status DisciplineServer::SetStreamOptions(ServerContext *context,
                                          const StreamOptions *request,
                                          Empty *response)
{
    stream_opts_ = *request;

    return Status::OK;
}

Status DisciplineServer::GetVariableDefinitions(ServerContext *context,
                                                const Empty *request,
                                                ServerWriter<VariableMetaData> *writer)
{
    VariableMetaData meta;

    for (const VariableMetaData &var : var_meta_)
        writer->Write(var);

    return Status::OK;
}

Status DisciplineServer::GetPartialDefinitions(ServerContext *context,
                                               const Empty *request,
                                               ServerWriter<PartialsMetaData> *writer)
{
    for (const PartialsMetaData &partial : partials_meta_)
        writer->Write(partial);

    return Status::OK;
}

grpc::Status DisciplineServer::Setup(grpc::ServerContext *context,
                                     const Empty *request,
                                     Empty *response)
{
    Setup();

    return Status::OK;
}

void DisciplineServer::Setup()
{
}