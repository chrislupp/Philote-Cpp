add_library(ExplicitServer OBJECT explicit_server.cpp)
set_property(TARGET ExplicitServer PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(ExplicitClient OBJECT explicit_client.cpp)
set_property(TARGET ExplicitClient PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(ImplicitServer OBJECT implicit_server.cpp)
set_property(TARGET ImplicitServer PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(ImplicitClient OBJECT implicit_client.cpp)
set_property(TARGET ImplicitClient PROPERTY POSITION_INDEPENDENT_CODE TRUE)