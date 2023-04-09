
#include <Philote/explicit_server.h>

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
    for (size_t i = 0; i < vars_.NumVariables(); i++)
    {
        /* code */
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