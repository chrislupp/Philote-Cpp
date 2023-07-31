
add_library(Variable OBJECT variable.cpp)
target_link_libraries(Variable PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(Partials OBJECT partials.cpp)
