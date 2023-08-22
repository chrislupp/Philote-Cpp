add_subdirectory(utils)
add_subdirectory(discipline)
add_subdirectory(explicit)
add_subdirectory(implicit)


add_library(PhiloteCpp STATIC
    $<TARGET_OBJECTS:GrpcGenerated>
    $<TARGET_OBJECTS:Utilities>
    $<TARGET_OBJECTS:Discipline>
    $<TARGET_OBJECTS:ExplicitDiscipline>
    $<TARGET_OBJECTS:ImplicitDiscipline>
)