add_library(Utilities OBJECT variable.cpp)
target_link_libraries(Utilities PRIVATE protobuf::libprotobuf gRPC::grpc++)
