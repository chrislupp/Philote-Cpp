
add_library(DisciplineServer OBJECT discipline_server.cpp)
target_link_libraries(DisciplineServer PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(ExplicitServer OBJECT explicit_server.cpp)
target_link_libraries(ExplicitServer PRIVATE protobuf::libprotobuf gRPC::grpc++)


add_library(ExplicitClient OBJECT explicit_client.cpp)
target_link_libraries(ExplicitClient PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(ImplicitServer OBJECT implicit_server.cpp)
target_link_libraries(ImplicitServer PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(ImplicitClient OBJECT implicit_client.cpp)
target_link_libraries(ImplicitClient PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(ServerHelpers OBJECT server_helpers.cpp)
target_link_libraries(ServerHelpers PRIVATE protobuf::libprotobuf gRPC::grpc++)