#include <vector>
#include <Philote/explicit_server.h>

using std::string;
using std::vector;

using google::protobuf::Empty;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using philote::ContArray;
using philote::DiscArray;
using philote::ExplicitServer;
using philote::Partials;
using philote::Variables;

ExplicitServer::ExplicitServer() {}

ExplicitServer::~ExplicitServer() {}

Status ExplicitServer::SetStreamOptions(ServerContext *context,
                                        const ::Options *request,
                                        Empty *response)
{
    // assign the options from the message
    stream_opts_.num_double = request->num_double();
    stream_opts_.num_int = request->num_int();

    return Status::OK;
}

Status ExplicitServer::DefineVariables(ServerContext *context,
                                       const Empty *request,
                                       ServerWriter<::VariableMetaData> *writer)
{
    // local variable before sending
    VariableMetaData meta;

    // iterate through all variables of the discipline
    for (const string &name : vars_.ListVariables())
    {
        // get the variable type
        VariableType type = vars_.Type(name);

        if (type == VariableType::kInput)
        {
            // set the flags to mark this as a continuous input
            // meta.set_input(true);
            // meta.set_discrete(false);
        }
        else if (type == VariableType::kDiscreteInput)
        {
            // set the flags to mark this as a discrete input
            // meta.set_input(true);
            // meta.set_discrete(true);
        }
        else if (type == VariableType::kOutput)
        {
            // set the flags to mark this as a continuous output
            // meta.set_input(false);
            // meta.set_discrete(false);
        }
        else if (type == VariableType::kDiscreteOutput)
        {
            // set the flags to mark this as a discrete output
            // meta.set_input(false);
            // meta.set_discrete(true);
        }

        // set the variable shape
        auto values = vars_.Shape(name);
        meta.mutable_shape()->Add(values.begin(), values.end());

        // set the units field
        meta.set_units(vars_.Units(name));

        // send the message
        writer->Write(meta);
    }

    return Status::OK;
}

Status ExplicitServer::DefinePartials(ServerContext *context,
                                      const Empty *request,
                                      ServerWriter<::PartialsMetaData> *writer)
{
    for (const string &out : vars_.ListVariables())
    {
        // local variable before sending
        PartialsMetaData meta;

        // skip the loop iteration if the variable isn't an output
        if (vars_.Type(out) != VariableType::kOutput)
            continue;

        // set the name field
        meta.set_name(vars_.Units(out));

        for (const string &in : vars_.ListVariables())
        {
            // skip the loop iteration if the variable isn't an input
            if (vars_.Type(out) != VariableType::kInput)
                continue;

            // set the subname field
            meta.set_name(vars_.Units(in));

            // send the message
            writer->Write(meta);
        }
    }

    return Status::OK;
}

Status ExplicitServer::Functions(ServerContext *context,
                                 ServerReaderWriter<::Array, ::Array> *stream)
{
    ::Array array;
    Variables inputs;

    // preallocate the inputs based on meta data

    while (stream->Read(&array))
    {

        // get variables from the stream message
        string name = array.name();
        auto start = array.start();
        auto end = array.end();

        // obtain the inputs and discrete inputs from the stream
        if (vars_.Type(name) == VariableType::kInput)
        {
            // get array data
            vector<double> value;
            value.assign(array.continuous().begin(), array.continuous().end());

            // set the variable slice
            inputs.SetContinuous(name, start, end, value);
        }
        else if (vars_.Type(name) == VariableType::kDiscreteInput)
        {
            // get array data
            vector<int64_t> value;
            value.assign(array.discrete().begin(), array.discrete().end());

            // set the variable slice
            inputs.SetDiscrete(name, start, end, value);
        }
        else
        {
            // error message
        }
    }

    // call the discipline developer-defined Compute function
    Variables outputs = Compute(inputs);

    // iterate through continuous outputs
    vector<string> var_list;
    for (auto &name : var_list)
    {

        // chunk the array
        for (size_t i = 0; i < 1; i++)
        {
            ::Array out_array;

            // set array name and meta data
            out_array.set_name(name);

            int64_t start, end;

            // set start and end of the chunk
            out_array.set_start(start);
            out_array.set_end(end);

            if (vars_.Type(name) == VariableType::kOutput)
            {
                vector<double> slice = outputs.ContinuousSlice(name, start, end);
                out_array.mutable_continuous()->Add(slice.begin(), slice.end());
            }
            else if (vars_.Type(name) == VariableType::kDiscreteOutput)
            {
                vector<int64_t> slice = outputs.DiscreteSlice(name, start, end);
                out_array.mutable_discrete()->Add(slice.begin(), slice.end());
            }
            else
            {
                // error message
            }

            // send the outputs back via stream
            stream->Write(out_array);
        }
    }

    return Status::OK;
}

Status ExplicitServer::Gradient(ServerContext *context,
                                ServerReaderWriter<::Array, ::Array> *stream)
{
    return Status::OK;
}

// these functions need to be overridden by discipline developers
//------------------------------------------------------------------------------
void ExplicitServer::Setup() {}

void ExplicitServer::SetupPartials() {}

Variables ExplicitServer::Compute(const Variables &inputs)
{
    return Variables();
}

Partials ExplicitServer::ComputePartials(const Variables &inputs)
{
    return Partials();
}