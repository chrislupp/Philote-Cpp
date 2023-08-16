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
#include <Philote/explicit.h>

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

ExplicitServer::~ExplicitServer()
{
    UnlinkPointers();
}

void ExplicitServer::LinkPointers(philote::DisciplineServer *discipline,
                                  philote::ExplicitDiscipline *implementation)
{
    discipline_ = discipline;
    implementation_ = implementation;
}

void ExplicitServer::UnlinkPointers()
{
    discipline_ = nullptr;
    implementation_ = nullptr;
}

Status ExplicitServer::ComputeFunction(ServerContext *context,
                                       ServerReaderWriter<::philote::Array,
                                                          ::philote::Array> *stream)
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
        auto var = std::find_if(discipline_->var_meta().begin(),
                                discipline_->var_meta().end(),
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

    // preallocate outputs
    Variables outputs;
    for (const VariableMetaData &var : discipline_->var_meta())
    {
        if (var.type() == kOutput)
            outputs[var.name()] = Variable(var);
    }

    // call the discipline developer-defined Compute function
    implementation_->Compute(inputs, outputs);

    // iterate through continuous outputs
    vector<string> var_list;
    for (auto &name : var_list)
    {
        outputs[name].Send(name, "", stream, discipline_->stream_opts().num_double());
    }

    return Status::OK;
}

Status ExplicitServer::ComputeGradient(ServerContext *context,
                                       ServerReaderWriter<::philote::Array,
                                                          ::philote::Array> *stream)
{
    return Status::OK;
}