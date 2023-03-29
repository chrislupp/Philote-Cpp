
add_library(Array OBJECT array.cpp)
set_property(TARGET Array PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(DiscreteArray OBJECT discrete_array.cpp)
set_property(TARGET DiscreteArray PROPERTY POSITION_INDEPENDENT_CODE TRUE)