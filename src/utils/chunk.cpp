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
#include <Philote/chunk.h>

using namespace philote;
using grpc::ClientReaderWriter;
using std::shared_ptr;

void SendChunkedArray(std::shared_ptr<grpc::ClientReaderWriter<::philote::Array, ::philote::Array>> stream,
                      const std::string &var_name,
                      philote::Variables &variables)
{
    ::philote::Array inputs;

    inputs.set_name(var_name);

    // chunk start and end indices within the serialized array
    inputs.set_start(0);
    inputs.set_end(1);

    stream->Write(inputs);
}

// DataArray<double> AssembleArray(std::vector<Array> &chunks)
// {
//     return DataArray<double>();
// }