
#include <Philote/explicit_client.h>

using namespace philote;

ExplicitClient::ExplicitClient() {}

ExplicitClient::~ExplicitClient() {}

void ExplicitClient::RemoteSetup()
{
    // call remote setup function
    std::vector<std::string> vars;
    std::vector<std::string> discrete_vars;
    std::vector<std::string> funcs;
    std::vector<std::string> discrete_funcs;

    // temp
    bool input = false;
    bool discrete = false;
    std::string name;
    std::vector<size_t> shape;
    std::string units;
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

void ExplicitClient::RemoteCompute(std::map<std::string, Array> &inputs,
                                   std::map<std::string, DiscreteArray> &discrete_inputs,
                                   std::map<std::string, Array> &outputs,
                                   std::map<std::string, DiscreteArray> &discrete_outputs)
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
        Array temp;

        // assign functions to map
        outputs[key] = temp;
    }

    // iterate through defined discrete functions for assignment
    for (auto &key : discrete_funcs_)
    {
        // data array for the function data
        DiscreteArray temp;

        // assign functions to map
        discrete_outputs[key] = temp;
    }
}

void ExplicitClient::RemotePartials(std::map<std::string, Array> &inputs,
                                    std::map<std::string, DiscreteArray> &discrete_inputs,
                                    std::map<std::pair<std::string, std::string>, Array> &partials)
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
        Array temp;

        // assign partials to map
        partials[key] = temp;
    }
}