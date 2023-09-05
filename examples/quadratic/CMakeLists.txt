
add_executable(ExampleQuadraticServer quadratic_server.cpp)
target_link_libraries(ExampleQuadraticServer
                        PhiloteCpp
                        protobuf::libprotobuf
                        gRPC::grpc++
)

add_executable(ExampleQuadraticClient quadratic_client.cpp)
target_link_libraries(ExampleQuadraticClient
                        PhiloteCpp
                        protobuf::libprotobuf
                        gRPC::grpc++
)