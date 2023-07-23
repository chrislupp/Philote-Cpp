add_subdirectory(general)
add_subdirectory(utils)

add_library(PhiloteCpp STATIC
    $<TARGET_OBJECTS:Array>
    $<TARGET_OBJECTS:DiscreteArray>
    $<TARGET_OBJECTS:Variables>
    $<TARGET_OBJECTS:ExplicitServer>
    $<TARGET_OBJECTS:ExplicitClient>
    $<TARGET_OBJECTS:ImplicitServer>
    $<TARGET_OBJECTS:ImplicitClient>
    $<TARGET_OBJECTS:ServerHelpers>
    $<TARGET_OBJECTS:GrpcGenerated>
)