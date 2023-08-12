
add_executable(ExampleParaboloid paraboloid_server.cpp)
target_link_libraries(ExampleParaboloid PhiloteCpp)
target_link_libraries(ExampleParaboloid protobuf::libprotobuf gRPC::grpc++)
