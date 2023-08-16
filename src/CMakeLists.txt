

add_library(PhiloteCpp STATIC
    ${CMAKE_SOURCE_DIR}/generated/data.pb.cc
    ${CMAKE_SOURCE_DIR}/generated/disciplines.grpc.pb.cc

    utils/variable.cpp

    discipline/discipline_server.cpp
    discipline/discipline.cpp
    discipline/discipline_client.cpp

    explicit/explicit_server.cpp
    explicit/explicit_discipline.cpp
    explicit/explicit_client.cpp

    implicit/implicit_server.cpp
    implicit/implicit_client.cpp
)

target_link_libraries(PhiloteCpp PRIVATE protobuf::libprotobuf gRPC::grpc++)