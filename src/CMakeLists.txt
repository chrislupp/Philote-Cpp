
add_subdirectory(discipline)
add_subdirectory(explicit)
add_subdirectory(implicit)
add_subdirectory(utils)

add_library(PhiloteCpp STATIC
    ${CMAKE_SOURCE_DIR}/generated/data.pb.cc
    ${CMAKE_SOURCE_DIR}/generated/disciplines.grpc.pb.cc

    $<TARGET_OBJECTS:Variable>
    
    $<TARGET_OBJECTS:DisciplineServer>
    $<TARGET_OBJECTS:Discipline>
    $<TARGET_OBJECTS:DisciplineClient>

    $<TARGET_OBJECTS:ExplicitServer>
    $<TARGET_OBJECTS:ExplicitDiscipline>
    $<TARGET_OBJECTS:ExplicitClient>
    
    $<TARGET_OBJECTS:ImplicitServer>
    $<TARGET_OBJECTS:ImplicitClient>
)
target_link_libraries(PhiloteCpp PRIVATE protobuf::libprotobuf gRPC::grpc++)