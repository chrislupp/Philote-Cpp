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

Status ExplicitServer::Functions(ServerContext *context,
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
            // inputs.SetContinuous(name, start, end, value);
        }
        else if (var->type() == VariableType::kDiscreteInput)
        {
            // get array data
            vector<int64_t> value;
            value.assign(array.discrete().begin(), array.discrete().end());

            // set the variable slice
            // inputs.SetDiscrete(name, start, end, value);
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
        // chunk the array
        for (size_t i = 0; i < 1; i++)
        {
            ::philote::Array out_array;

            // set array name and meta data
            out_array.set_name(name);

            int64_t start, end;

            // set start and end of the chunk
            out_array.set_start(start);
            out_array.set_end(end);

            // get the variable corresponding to the current message
            auto var = std::find_if(var_meta_.begin(), var_meta_.end(),
                                    [&name](const VariableMetaData &var)
                                    { return var.name() == name; });

            if (var->type() == VariableType::kOutput)
            {
                // vector<double> slice = outputs.ContinuousSlice(name, start, end);
                // out_array.mutable_continuous()->Add(slice.begin(), slice.end());
            }
            else if (var->type() == VariableType::kDiscreteOutput)
            {
                // vector<int64_t> slice = outputs.DiscreteSlice(name, start, end);
                // out_array.mutable_discrete()->Add(slice.begin(), slice.end());
            }
            else
            {
                // error message
            }

            // send the outputs back via stream
            stream->Write(out_array);
        }
    }

    return Status::OK;
}

Status ExplicitServer::Gradient(ServerContext *context,
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