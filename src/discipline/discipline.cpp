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

void DisciplineServer::AddInput(const string &name,
                                const vector<int64_t> &shape,
                                const string &units)
{
    VariableMetaData var;
    var.set_name(name);
    for (const int64_t dim : shape)
        var.add_shape(dim);
    var.set_units(units);
    var.set_type(philote::kInput);

    var_meta_.push_back(var);
}

void DisciplineServer::AddOutput(const string &name,
                                 const vector<int64_t> &shape,
                                 const string &units)
{
    VariableMetaData var;
    var.set_name(name);
    for (const int64_t dim : shape)
        var.add_shape(dim);
    var.set_units(units);
    var.set_type(philote::kOutput);

    var_meta_.push_back(var);
}

void DisciplineServer::DeclarePartials(const string &f, const string &x)
{
    PartialsMetaData meta;
    meta.set_name(f);
    meta.set_subname(x);

    partials_meta_.push_back(meta);
}