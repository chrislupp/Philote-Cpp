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
#include <Philote/implicit.h>

using std::shared_ptr;
using std::string;

using grpc::ChannelInterface;
using grpc::ClientContext;
using grpc::ClientReaderWriter;

using philote::ImplicitClient;
using philote::Partials;
using philote::Variables;

void ImplicitClient::ConnectChannel(shared_ptr<ChannelInterface> channel)
{
    DisciplineClient::ConnectChannel(channel);
    stub_ = ImplicitService::NewStub(channel);
}

Variables ImplicitClient::ComputeResiduals(const Variables &vars)
{
    ClientContext context;
    std::shared_ptr<ClientReaderWriter<Array, Array>>
        stream(stub_->ComputeResiduals(&context));

    // send/assign inputs and preallocate outputs
    Variables outputs;

    for (const VariableMetaData &var : var_meta_)
    {
        const string name = var.name();

        if (var.type() == kInput)
            vars.at(name).Send(name, "", stream, stream_options_.num_double());

        if (var.type() == kOutput)
            vars.at(name).Send(name, "", stream, stream_options_.num_double());
    }

    // finish streaming data to the server
    stream->WritesDone();

    Array result;
    while (stream->Read(&result))
    {
        const string name = result.name();
        outputs[name].AssignChunk(result);
    }

    grpc::Status status = stream->Finish();

    return outputs;
}

Variables ImplicitClient::SolveResiduals(const Variables &vars)
{
    return Variables();
}

Partials ImplicitClient::ComputeResidualGradients(const Variables &inputs)
{
    return Partials();
}
