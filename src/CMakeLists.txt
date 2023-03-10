
add_library(ExplicitServer OBJECT explicit_server.cpp)
set_property(TARGET ExplicitServer PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(ExplicitClient OBJECT explicit_client.cpp)
set_property(TARGET ExplicitClient PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(ImplicitServer OBJECT implicit_server.cpp)
set_property(TARGET ImplicitServer PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(ImplicitClient OBJECT implicit_client.cpp)
set_property(TARGET ImplicitClient PROPERTY POSITION_INDEPENDENT_CODE TRUE)


add_library(PhiloteCpp SHARED
    $<TARGET_OBJECTS:ExplicitServer>
    $<TARGET_OBJECTS:ExplicitClient>
    $<TARGET_OBJECTS:ImplicitServer>
    $<TARGET_OBJECTS:ImplicitClient>
)

# set position independent code property
set_property(TARGET PhiloteCpp PROPERTY POSITION_INDEPENDENT_CODE TRUE)