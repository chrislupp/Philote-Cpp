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
#include <Philote/discipline_client.h>

using google::protobuf::Empty;
using grpc::ClientContext;
using grpc::ClientReader;
using philote::DisciplineProperties;
using philote::VariableMetaData;
using std::string;
using std::vector;

using namespace philote;

DisciplineClient::DisciplineClient()
{
    // set default streaming options
    stream_options_.set_num_double(1000);
    stream_options_.set_num_int(1000);
}

void DisciplineClient::GetInfo()
{
    ClientContext context;
    Empty request;

    stub_->GetInfo(&context, request, &properties_);
}

void DisciplineClient::SendStreamOptions()
{
    ClientContext context;
    ::google::protobuf::Empty response;

    stub_->SetStreamOptions(&context, stream_options_, &response);
}

void DisciplineClient::SendOptions()
{
}

void DisciplineClient::Setup()
{
    ClientContext context;
    ::google::protobuf::Empty request, response;

    stub_->Setup(&context, request, &response);
}

void DisciplineClient::GetVariableDefinitions()
{
    ClientContext context;
    Empty request;
    std::unique_ptr<ClientReader<VariableMetaData>> reactor;

    reactor = stub_->GetVariableDefinitions(&context, request);
}

void DisciplineClient::GetPartialDefinitions()
{
    ClientContext context;
    Empty request;
    std::unique_ptr<ClientReader<PartialsMetaData>> reactor;

    reactor = stub_->GetPartialDefinitions(&context, request);
}

vector<string> GetVariableNames()
{
    return vector<string>();
}

VariableMetaData DisciplineClient::GetVariableMeta(const string &name)
{
    return VariableMetaData();
}

void DisciplineClient::AddVariableMeta(const philote::VariableMetaData &var)
{
    var_meta_.push_back(var);
}