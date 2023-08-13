

add_library(ServerHelpers OBJECT server_helpers.cpp)
target_link_libraries(ServerHelpers PRIVATE protobuf::libprotobuf gRPC::grpc++)