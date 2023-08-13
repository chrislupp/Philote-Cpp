
add_library(DisciplineServer OBJECT discipline_server.cpp )
target_link_libraries(DisciplineServer PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(DisciplineClient OBJECT discipline_client.cpp)
target_link_libraries(DisciplineClient PRIVATE protobuf::libprotobuf gRPC::grpc++)

add_library(Discipline OBJECT discipline.cpp)
target_link_libraries(Discipline PRIVATE protobuf::libprotobuf gRPC::grpc++)