

add_library(ExplicitDiscipline OBJECT explicit_discipline.cpp)
target_link_libraries(ExplicitDiscipline PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(ExplicitServer OBJECT explicit_server.cpp)
target_link_libraries(ExplicitServer PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(ExplicitClient OBJECT explicit_client.cpp)
target_link_libraries(ExplicitClient PRIVATE protobuf::libprotobuf gRPC::grpc++)