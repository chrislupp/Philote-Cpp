
#include <Philote/explicit_server.h>

using google::protobuf::Empty;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using namespace philote;

ExplicitServer::ExplicitServer() {}

ExplicitServer::~ExplicitServer() {}

Status SetStreamOptions(ServerContext *context,
                        const ::Options *request,
                        Empty *response)
{
    // request->name();
    return Status::OK;
}

Status DefineVariables(ServerContext *context,
                       const Empty *request,
                       ServerWriter<::VariableMetaData> *writer)
{
    return Status::OK;
}

Status DefinePartials(ServerContext *context,
                      const Empty *request,
                      ServerWriter<::PartialsMetaData> *writer)
{
    return Status::OK;
}

Status Functions(ServerContext *context,
                 ServerReaderWriter<::Array, ::Array> *stream)
{
    return Status::OK;
}

Status Gradient(ServerContext *context,
                ServerReaderWriter<::Array, ::Array> *stream)
{
    return Status::OK;
}

// these functions need to be overridden by discipline developers
//------------------------------------------------------------------------------
void ExplicitServer::Setup()
{
}

void ExplicitServer::SetupPartials() {}

void ExplicitServer::Compute() {}

void ExplicitServer::ComputePartials() {}