add_subdirectory(general)
add_subdirectory(discipline)
add_subdirectory(explicit)
add_subdirectory(implicit)
add_subdirectory(utils)

add_library(PhiloteCpp STATIC
    $<TARGET_OBJECTS:Variable>
    $<TARGET_OBJECTS:ExplicitServer>
    $<TARGET_OBJECTS:ExplicitClient>
    $<TARGET_OBJECTS:ImplicitServer>
    $<TARGET_OBJECTS:ImplicitClient>
    $<TARGET_OBJECTS:ServerHelpers>
    $<TARGET_OBJECTS:GrpcGenerated>
)