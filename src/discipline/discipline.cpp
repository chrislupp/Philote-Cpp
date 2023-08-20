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
#include <Philote/discipline.h>

using std::string;
using std::vector;

using philote::Discipline;
using philote::DisciplineProperties;
using philote::StreamOptions;

Discipline::Discipline()
{
    discipline_server_.LinkPointers(this);
}

std::vector<philote::VariableMetaData> &Discipline::var_meta()
{
    return var_meta_;
}

std::vector<philote::PartialsMetaData> &Discipline::partials_meta()
{
    return partials_meta_;
}

DisciplineProperties &Discipline::properties()
{
    return properties_;
}

StreamOptions &Discipline::stream_opts()
{
    return stream_opts_;
}

void Discipline::AddInput(const string &name,
                          const vector<int64_t> &shape,
                          const string &units)
{
    VariableMetaData var;
    var.set_name(name);
    for (const int64_t dim : shape)
        var.add_shape(dim);
    var.set_units(units);
    var.set_type(philote::kInput);

    var_meta().push_back(var);
}

void Discipline::AddOutput(const string &name,
                           const vector<int64_t> &shape,
                           const string &units)
{
    VariableMetaData var;
    var.set_name(name);
    for (const int64_t dim : shape)
        var.add_shape(dim);
    var.set_units(units);
    var.set_type(philote::kOutput);

    var_meta().push_back(var);
}

void Discipline::DeclarePartials(const string &f, const string &x)
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

        if (var.name() == x and var.type() == kInput)
        {
            for (const auto &dim : var.shape())
                shape_x.push_back(dim);
        }
    }
    vector<int64_t> shape(shape_f.size() + shape_x.size());
    shape.insert(shape.end(), shape_f.begin(), shape_f.end());
    shape.insert(shape.end(), shape_x.begin(), shape_x.end());

    PartialsMetaData meta;
    meta.set_name(f);
    meta.set_subname(x);
    for (const auto &dim : shape)
        meta.add_shape(dim);

    partials_meta_.push_back(meta);
}

void Discipline::Setup()
{
}

void Discipline::SetupPartials()
{
}