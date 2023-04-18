
#include <Philote/array.h>
#include <Philote/explicit_client.h>

// protobuf/gRPC generated header
#include <array.pb.h>
#include <metadata.pb.h>
#include <options.pb.h>
#include <explicit.pb.h>
#include <explicit.grpc.pb.h>

// namespace statements for readibility
using std::map;
using std::pair;
using std::string;
using std::vector;
using namespace philote;

ExplicitClient::ExplicitClient() {}

ExplicitClient::~ExplicitClient() {}

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
    // assign inputs
    for (auto &key : vars_)
    {
    }

    // assign discrete inputs
    for (auto &key : discrete_vars_)
    {
    }

    // call remote function evaluation

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
}

void ExplicitClient::RemotePartials(map<string, ContArray> &inputs,
                                    map<string, DiscArray> &discrete_inputs,
                                    map<pair<string, string>, ContArray> &partials)
{
    // assign inputs
    for (auto &key : vars_)
    {
    }

    // assign discrete inputs
    for (auto &key : discrete_vars_)
    {
    }

    // call remote gradient evaluation

    // iterate through defined partials for assignment
    for (auto &key : partials_)
    {
        // data array for the partials
        ContArray temp;

        // assign partials to map
        partials[key] = temp;
    }
}