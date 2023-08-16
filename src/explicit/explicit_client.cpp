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
#include <Philote/explicit.h>

#include <data.pb.h>
#include <disciplines.pb.h>
#include <disciplines.grpc.pb.h>

using grpc::ChannelInterface;
using philote::ExplicitClient;
using philote::VariableMetaData;

using std::map;
using std::pair;
using std::string;
using std::vector;

ExplicitClient::ExplicitClient()
{
    // default host name
    host_ = "localhost:50051";
}

ExplicitClient::ExplicitClient(const std::string &host)
{
    host_ = host;
}

ExplicitClient::~ExplicitClient() {}

void ExplicitClient::ConnectChannel(std::shared_ptr<ChannelInterface> channel)
{
    DisciplineClient::ConnectChannel(channel);
    stub_ = ExplicitService::NewStub(channel);
}

philote::Variables ExplicitClient::ComputeFunction(Variables &inputs)
{
    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<::philote::Array, ::philote::Array>>
        stream(stub_->ComputeFunction(&context));

    // assign inputs
    for (const VariableMetaData &var : var_meta_)
    {
        const string name = var.name();
        inputs[name].Send(name, "", stream, stream_options_.num_double());
    }

    // preallocate outputs
    Variables outputs;
    for (const VariableMetaData &var : var_meta_)
    {
        if (var.type() == kOutput)
            outputs[var.name()] = Variable(var);
    }

    // finish streaming data to the server
    stream->WritesDone();

    ::philote::Array result;
    while (stream->Read(&result))
    {
        const string name = result.name();
        outputs[name].AssignChunk(result);
    }

    grpc::Status status = stream->Finish();

    return outputs;
}

// void ExplicitClient::ComputeGradient(map<string, ContArray> &inputs,
//                                      map<string, DiscArray> &discrete_inputs,
//                                      map<pair<string, string>, ContArray> &partials)
// {
//     grpc::ClientContext context;
//     std::shared_ptr<grpc::ClientReaderWriter<::philote::Array, ::philote::Array>>
//         stream(stub_->ComputeGradient(&context));

//     // assign inputs
//     for (const VariableMetaData &var : var_meta_)
//     {
//         const string name = var.name();
//         inputs[name].Send(stream, stream_options_.num_double());
//     }

//     // finish streaming data to the server
//     stream->WritesDone();

//     ::philote::Array result;
//     while (stream->Read(&result))
//     {
//         const string name = result.name();
//         outputs[name].AssignChunk(result);
//     }

//     grpc::Status status = stream->Finish();
// }