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

using google::protobuf::Struct;

using grpc::Server;
using grpc::ServerBuilder;

using philote::ExplicitDiscipline;
using philote::Partials;
using philote::Variables;

using std::make_pair;
using std::pow;

class Rosenbrock : public ExplicitDiscipline
{
public:
    // Constructor
    Rosenbrock() = default;

    // Destructor
    ~Rosenbrock() = default;

private:
    // dimension of the Rosenbrock function
    int64_t n_;

    // set options
    void Initialize(const Struct &options)
    {
        n_ = options.fields().find("n")->second.number_value();
    }

    // Defines the variables for the discipline
    void Setup()
    {
        AddInput("x", {n_}, "m");

        AddOutput("f", {n_}, "m**2");
    }

    // Defines the partials for the discipline
    void SetupPartials()
    {
        DeclarePartials("f", "x");
    }

    // Computes
    void Compute(const philote::Variables &inputs, philote::Variables &outputs)
    {
        double x = inputs.at("x")(0);

        outputs.at("f")(0) = pow(x - 3.0, 2.0);
    }

    void ComputePartials(const philote::Variables &inputs, Partials &jac)
    {
        double x = inputs.at("x")(0);

        jac[make_pair("f", "x")](0) = 2.0;
    }
};

int main()
{
    std::string address("localhost:50051");
    Rosenbrock service;

    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    service.RegisterServices(builder);

    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();

    return 0;
}