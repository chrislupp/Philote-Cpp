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

    This work has been cleared for public release, distribution unlimited, case
    number: AFRL-2023-5716.

    The views expressed are those of the authors and do not reflect the
    official guidance or position of the United States Government, the
    Department of Defense or of the United States Air Force.

    Statement from DoD: The Appearance of external hyperlinks does not
    constitute endorsement by the United States Department of Defense (DoD) of
    the linked websites, of the information, products, or services contained
    therein. The DoD does not exercise any editorial, security, or other
    control over the information you may find at these locations.
*/
#include <grpcpp/grpcpp.h>

#include "implicit.h"

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

void ImplicitDiscipline::DeclarePartials(const string &f, const string &x)
{

    // determine and assign the shape of the partials array
    vector<int64_t> shape_f, shape_x;
    for (const auto &var : var_meta_)
    {
        if (var.name() == f and var.type() == kOutput)
        {
            for (const auto &dim : var.shape())
                shape_f.push_back(dim);
        }

        if (var.name() == x and (var.type() == kInput or var.type() == kOutput))
        {
            for (const auto &dim : var.shape())
                shape_x.push_back(dim);
        }
    }

    // create the combined shape array
    vector<int64_t> shape;

    if (shape_f.size() == 1 and shape_f[0] == 1 and shape_x.size() == 1 and shape_x[0] == 1)
    {
        shape.resize(1);
        shape[0] = 1;
    }
    else if (shape_f.size() == 1 and shape_f[0] == 1)
    {
        shape.resize(shape_x.size());
        shape = shape_x;
    }
    else if (shape_x.size() == 1 and shape_x[0] == 1)
    {
        shape.resize(shape_f.size());
        shape = shape_f;
    }
    else
    {
        shape.resize(shape_f.size() + shape_x.size());
        shape.insert(shape.end(), shape_f.begin(), shape_f.end());
        shape.insert(shape.end(), shape_x.begin(), shape_x.end());
    }

    // assign the meta data
    PartialsMetaData meta;
    meta.set_name(f);
    meta.set_subname(x);
    for (const auto &dim : shape)
        meta.add_shape(dim);

    partials_meta_.push_back(meta);
}

void ImplicitDiscipline::ComputeResiduals(const Variables &inputs,
                                          const philote::Variables &outputs,
                                          philote::Variables &residuals)
{
}

void ImplicitDiscipline::SolveResiduals(const Variables &inputs,
                                        philote::Variables &outputs)
{
}

void ImplicitDiscipline::ComputeResidualGradients(const Variables &inputs,
                                                  const philote::Variables &outputs,
                                                  Partials &partials)
{
}