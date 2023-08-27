
add_library(ImplicitDiscipline OBJECT
    implicit_server.cpp
    implicit_discipline.cpp
    implicit_client.cpp
)
target_link_libraries(ImplicitDiscipline PRIVATE protobuf::libprotobuf gRPC::grpc++)
