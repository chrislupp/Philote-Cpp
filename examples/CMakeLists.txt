
add_executable(ExampleParaboloidServer paraboloid_server.cpp)
target_link_libraries(ExampleParaboloidServer
                        PhiloteCpp
                        protobuf::libprotobuf
                        gRPC::grpc++
)



add_executable(ExampleParaboloidClient paraboloid_client.cpp)
target_link_libraries(ExampleParaboloidClient
                        PhiloteCpp
                        protobuf::libprotobuf
                        gRPC::grpc++
)