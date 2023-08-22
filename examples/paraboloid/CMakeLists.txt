
add_executable(ExampleParaboloidServer paraboloid_server.cpp)
target_link_libraries(ExampleParaboloidServer PhiloteCpp)
target_link_libraries(ExampleParaboloidServer gRPC::grpc++)
target_link_libraries(ExampleParaboloidServer protobuf::libprotobuf)


add_executable(ExampleParaboloidClient paraboloid_client.cpp)
target_link_libraries(ExampleParaboloidClient
                        PhiloteCpp
                        protobuf::libprotobuf
                        gRPC::grpc++
)