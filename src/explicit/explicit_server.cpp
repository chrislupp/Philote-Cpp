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

using std::make_pair;
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

void ExplicitServer::LinkPointers(philote::ExplicitDiscipline *implementation)
{
    implementation_ = implementation;
}

void ExplicitServer::UnlinkPointers()
{
    implementation_ = nullptr;
}

Status ExplicitServer::ComputeFunction(ServerContext *context,
                                       ServerReaderWriter<::philote::Array,
                                                          ::philote::Array> *stream)
{
    philote::Array array;

    // preallocate the inputs based on meta data
    Variables inputs;
    for (auto &var : implementation_->var_meta())
    {
        string name = var.name();
        if (var.type() == kInput)
            inputs[name] = Variable(var);
    }

    while (stream->Read(&array))
    {
        // get variables from the stream message
        const string &name = array.name();
        auto start = array.start();
        auto end = array.end();

        // get the variable corresponding to the current message
        auto var = std::find_if(implementation_->var_meta().begin(),
                                implementation_->var_meta().end(),
                                [&name](const VariableMetaData &var)
                                { return var.name() == name; });

        // obtain the inputs and discrete inputs from the stream
        if (var->type() == VariableType::kInput)
        {
            // set the variable slice
            inputs[name].AssignChunk(array);
        }
        else
        {
            // error message
        }
    }

    // preallocate outputs
    Variables outputs;
    for (const VariableMetaData &var : implementation_->var_meta())
    {
        if (var.type() == kOutput)
            outputs[var.name()] = Variable(var);
    }

    // call the discipline developer-defined Compute function
    implementation_->Compute(inputs, outputs);

    // iterate through continuous outputs
    for (const VariableMetaData &var : implementation_->var_meta())
    {
        const string &name = var.name();

        if (var.type() == kOutput)
            outputs[name].Send(name, "", stream, implementation_->stream_opts().num_double());
    }

    return Status::OK;
}

Status ExplicitServer::ComputeGradient(ServerContext *context,
                                       ServerReaderWriter<::philote::Array,
                                                          ::philote::Array> *stream)
{
    philote::Array array;

    // preallocate the inputs based on meta data
    Variables inputs;
    for (const auto &var : implementation_->var_meta())
    {
        string name = var.name();
        if (var.type() == kInput)
            inputs[name] = Variable(var);
    }

    while (stream->Read(&array))
    {
        // get variables from the stream message
        const string &name = array.name();
        const auto &start = array.start();
        const auto &end = array.end();

        // get the variable corresponding to the current message
        const auto &var = std::find_if(implementation_->var_meta().begin(),
                                       implementation_->var_meta().end(),
                                       [&name](const VariableMetaData &var)
                                       { return var.name() == name; });

        // obtain the inputs and discrete inputs from the stream
        if (var->type() == VariableType::kInput)
        {
            // set the variable slice
            inputs[name].AssignChunk(array);
        }
        else
        {
            // error message
        }
    }

    // preallocate outputs
    Partials partials;
    for (const PartialsMetaData &par : implementation_->partials_meta())
    {
        vector<size_t> shape;
        for (const int64_t &dim : par.shape())
            shape.push_back(dim);

        partials[make_pair(par.name(), par.subname())] = Variable(kOutput, shape);
    }

    // call the discipline developer-defined Compute function
    implementation_->ComputePartials(inputs, partials);

    // iterate through partials
    for (const PartialsMetaData &par : implementation_->partials_meta())
    {
        const string &name = par.name();
        const string &subname = par.subname();

        partials[make_pair(name, subname)].Send(name, subname, stream, implementation_->stream_opts().num_double());
    }

    return Status::OK;
}