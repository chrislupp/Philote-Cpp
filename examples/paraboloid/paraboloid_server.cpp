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
#include <cmath>

#include <grpcpp/grpcpp.h>

#include <Philote/explicit.h>

using grpc::Server;
using grpc::ServerBuilder;

using philote::ExplicitDiscipline;
using philote::Partials;
using philote::Variables;

using std::make_pair;
using std::pow;

class RemoteParaboloid : public ExplicitDiscipline
{
public:
    // Constructor
    RemoteParaboloid() = default;

    // Destructor
    ~RemoteParaboloid() = default;

private:
    // Defines the variables for the discipline
    void Setup()
    {
        AddInput("x", {1}, "m");
        AddInput("y", {1}, "m");

        AddOutput("f_xy", {1}, "m**2");
    }

    // Defines the partials for the discipline
    void SetupPartials()
    {
        DeclarePartials("f_xy", "x");
        DeclarePartials("f_xy", "y");
    }

    // Computes
    void Compute(const philote::Variables &inputs, philote::Variables &outputs)
    {
        double x = inputs.at("x")(0);
        double y = inputs.at("y")(0);

        outputs.at("f_xy")(0) = pow(x - 3.0, 2.0) + x * y +
                                pow(y + 4.0, 2.0) - 3.0;
    }

    void ComputePartials(const philote::Variables &inputs, Partials &jac)
    {
        double x = inputs.at("x")(0);
        double y = inputs.at("y")(0);

        jac[make_pair("f_xy", "x")](0) = 2.0 * x - 6.0 + y;
        jac[make_pair("f_xy", "y")](0) = 2.0 * y + 8.0 + x;
    }
};

int main()
{
    std::string address("localhost:50051");
    RemoteParaboloid service;

    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    service.RegisterServices(builder);

    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();

    return 0;
}