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
#include <grpcpp/grpcpp.h>

#include <Philote/implicit.h>

using std::string;
using std::vector;

using grpc::Server;
using grpc::ServerBuilder;

using philote::ImplicitDiscipline;
using philote::Partials;
using philote::Variables;

ImplicitDiscipline::ImplicitDiscipline()
{
    // link to discipline server and this object
    implicit_.LinkPointers(this);
}

ImplicitDiscipline::~ImplicitDiscipline()
{
    implicit_.UnlinkPointers();
}

void ImplicitDiscipline::RegisterServices(ServerBuilder &builder)
{
    builder.RegisterService(&discipline_server_);
    builder.RegisterService(&implicit_);
}

void ImplicitDiscipline::AddOutput(const string &name,
                                   const vector<int64_t> &shape,
                                   const string &units)
{
    VariableMetaData var;
    var.set_name(name);
    for (const int64_t dim : shape)
        var.add_shape(dim);
    var.set_units(units);
    var.set_type(philote::kOutput);

    // add the output
    var_meta().push_back(var);

    // add the residual
    var.set_type(philote::kResidual);
    var_meta().push_back(var);
}

void ImplicitDiscipline::ComputeResiduals(const Variables &inputs,
                                          philote::Variables &outputs,
                                          philote::Variables &residuals)
{
}

void ImplicitDiscipline::SolveResiduals(const Variables &inputs,
                                        philote::Variables &outputs)
{
}

void ImplicitDiscipline::ComputeResidualGradients(const Variables &inputs,
                                                  Partials &partials)
{
}