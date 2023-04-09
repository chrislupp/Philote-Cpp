
#include <Philote/explicit_server.h>

using std::string;

using google::protobuf::Empty;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using philote::ExplicitServer;

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
    VariableMetaData var;

    // iterate through all variables of the discipline
    for (const string &name : vars_.ListVariables())
    {
        // get the variable type
        VariableType type = vars_.Type(name);

        if (type == VariableType::kInput)
        {
            // set the flags to mark this as a continuous input
            var.set_input(true);
            var.set_discrete(false);
        }
        else if (type == VariableType::kDiscreteInput)
        {
            // set the flags to mark this as a discrete input
            var.set_input(true);
            var.set_discrete(true);
        }
        else if (type == VariableType::kOutput)
        {
            // set the flags to mark this as a continuous output
            var.set_input(false);
            var.set_discrete(false);
        }
        else if (type == VariableType::kDiscreteOutput)
        {
            // set the flags to mark this as a discrete output
            var.set_input(false);
            var.set_discrete(true);
        }

        // set the variable shape
        auto shape_field = var.mutable_shape();
        // shape_field->CopyFrom(vars_.Shape(name));

        // send the message
    }

    return Status::OK;
}

Status ExplicitServer::DefinePartials(ServerContext *context,
                                      const Empty *request,
                                      ServerWriter<::PartialsMetaData> *writer)
{
    return Status::OK;
}

Status ExplicitServer::Functions(ServerContext *context,
                                 ServerReaderWriter<::Array, ::Array> *stream)
{
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

void ExplicitServer::Compute() {}

void ExplicitServer::ComputePartials() {}