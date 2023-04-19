
#include <Philote/array.h>
#include <Philote/explicit_client.h>

// protobuf/gRPC generated header
#include <array.pb.h>
#include <metadata.pb.h>
#include <options.pb.h>
#include <explicit.pb.h>
#include <explicit.grpc.pb.h>

// namespace statements for readibility
using philote::ExplicitClient;
using std::map;
using std::pair;
using std::string;
using std::vector;

ExplicitClient::ExplicitClient()
{
    // default host name
    host_ = "localhost:50051";
}

ExplicitClient::ExplicitClient(const std::string &host)
{
    host_ = host;
}

ExplicitClient::~ExplicitClient() {}

void ExplicitClient::Connect()
{
    // Create a gRPC channel and stub
    auto channel = grpc::CreateChannel(host_,
                                       grpc::InsecureChannelCredentials());
    auto stub = ExplicitDiscipline::NewStub(channel);
}

void ExplicitClient::RemoteSetup()
{
    // call remote setup function
    vector<string> vars;
    vector<string> discrete_vars;
    vector<string> funcs;
    vector<string> discrete_funcs;

    // temp
    bool input = false;
    bool discrete = false;
    string name;
    vector<size_t> shape;
    string units;
    for (size_t i = 0; i < 0; i++)
    {
        if (input)
        {
            if (discrete)
            {
                // assign name
                vars_.push_back(name);
                vars_shape_[name] = shape;
                vars_units_[name] = units;
            }
            else
            {
                // assign name
                discrete_vars_.push_back(name);
                discrete_vars_shape_[name] = shape;
                discrete_vars_units_[name] = units;
            }
        }
        else
        {
            if (discrete)
            {
                // assign name
                funcs_.push_back(name);
                funcs_shape_[name] = shape;
                funcs_units_[name] = units;
            }
            else
            {
                // assign name
                discrete_funcs_.push_back(name);
                discrete_funcs_shape_[name] = shape;
                discrete_funcs_units_[name] = units;
            }
        }
    }
}

void ExplicitClient::RemoteCompute(map<string, ContArray> &inputs,
                                   map<string, DiscArray> &discrete_inputs,
                                   map<string, ContArray> &outputs,
                                   map<string, DiscArray> &discrete_outputs)
{
    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<::Array, ::Array>> stream(
        stub_->Functions(&context));

    // assign inputs
    for (auto &key : vars_)
    {
        ::Array inputs;

        inputs.set_name("hello");

        inputs.set_start(0);
        inputs.set_end(1);

        // inputs.set_continuous({0});
    }

    // assign discrete inputs
    for (auto &key : discrete_vars_)
    {
        ::Array dinputs;

        dinputs.set_name("hello");

        dinputs.set_start(0);
        dinputs.set_end(1);
    }

    // finish streaming data to the server
    stream->WritesDone();

    ::Array result;
    while (stream->Read(&result))
    {
        continue;
    }

    // iterate through defined functions for assignment
    for (auto &key : funcs_)
    {
        // data array for the function data
        ContArray temp;

        // assign functions to map
        outputs[key] = temp;
    }

    // iterate through defined discrete functions for assignment
    for (auto &key : discrete_funcs_)
    {
        // data array for the function data
        DiscArray temp;

        // assign functions to map
        discrete_outputs[key] = temp;
    }

    grpc::Status status = stream->Finish();
}

void ExplicitClient::RemotePartials(map<string, ContArray> &inputs,
                                    map<string, DiscArray> &discrete_inputs,
                                    map<pair<string, string>, ContArray> &partials)
{
    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<::Array, ::Array>> stream(
        stub_->Gradient(&context));

    // assign inputs
    for (auto &key : vars_)
    {
    }

    // assign discrete inputs
    for (auto &key : discrete_vars_)
    {
    }

    // finish streaming data to the server
    stream->WritesDone();

    ::Array result;
    while (stream->Read(&result))
    {
        continue;
    }

    // iterate through defined partials for assignment
    for (auto &key : partials_)
    {
        // data array for the partials
        ContArray temp;

        // assign partials to map
        partials[key] = temp;
    }

    grpc::Status status = stream->Finish();
}