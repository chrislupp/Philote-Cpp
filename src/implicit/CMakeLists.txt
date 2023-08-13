
add_library(ImplicitServer OBJECT implicit_server.cpp)
target_link_libraries(ImplicitServer PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(ImplicitClient OBJECT implicit_client.cpp)
target_link_libraries(ImplicitClient PRIVATE protobuf::libprotobuf gRPC::grpc++)