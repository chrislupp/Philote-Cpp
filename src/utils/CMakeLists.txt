
add_library(ChunkUtils OBJECT chunk.cpp)
target_link_libraries(ChunkUtils PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(Variable OBJECT variable.cpp)
target_link_libraries(Variable PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(Partials OBJECT partials.cpp)
