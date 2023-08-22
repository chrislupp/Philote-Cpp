add_library(ExplicitDiscipline OBJECT
    explicit_server.cpp
    explicit_discipline.cpp
    explicit_client.cpp
)
target_link_libraries(ExplicitDiscipline PRIVATE protobuf::libprotobuf gRPC::grpc++)