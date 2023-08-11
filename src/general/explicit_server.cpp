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
using philote::ExplicitServer;
using philote::Partials;
using philote::Variables;

Status ExplicitServer::ComputeFunction(ServerContext *context,
                                       ServerReaderWriter<::philote::Array, ::philote::Array> *stream)
{
    ::philote::Array array;
    Variables inputs;

    // preallocate the inputs based on meta data
    while (stream->Read(&array))
    {

        // get variables from the stream message
        string name = array.name();
        auto start = array.start();
        auto end = array.end();

        // get the variable corresponding to the current message
        auto var = std::find_if(var_meta_.begin(), var_meta_.end(),
                                [&name](const VariableMetaData &var)
                                { return var.name() == name; });

        // obtain the inputs and discrete inputs from the stream
        if (var->type() == VariableType::kInput)
        {
            // get array data
            vector<double> value;
            value.assign(array.continuous().begin(), array.continuous().end());

            // set the variable slice
            inputs[name].Segment(start, end, value);
        }
        else if (var->type() == VariableType::kDiscreteInput)
        {
            // discrete data
        }
        else
        {
            // error message
        }
    }

    // call the discipline developer-defined Compute function
    Variables outputs = Compute(inputs);

    // iterate through continuous outputs
    vector<string> var_list;
    for (auto &name : var_list)
    {
        outputs[name].Send(stream, stream_opts_.num_double());
    }

    return Status::OK;
}

Status ExplicitServer::ComputeGradient(ServerContext *context,
                                       ServerReaderWriter<::philote::Array,
                                                          ::philote::Array> *stream)
{
    return Status::OK;
}

// these functions need to be overridden by discipline developers
//------------------------------------------------------------------------------
void ExplicitServer::Setup() {}

void ExplicitServer::SetupPartials() {}

Variables ExplicitServer::Compute(const ::philote::Variables &inputs)
{
    return Variables();
}

Partials ExplicitServer::ComputePartials(const ::philote::Variables &inputs)
{
    return Partials();
}