add_library(Discipline OBJECT
    discipline_server.cpp
    discipline.cpp
    discipline_client.cpp
)
target_link_libraries(Discipline PRIVATE protobuf::libprotobuf gRPC::grpc++)
