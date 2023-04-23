
add_library(Array OBJECT array.cpp)
target_compile_definitions(Array PRIVATE TYPE=double)

add_library(DiscreteArray OBJECT array.cpp)
target_compile_definitions(DiscreteArray PRIVATE TYPE=long)

add_library(VariableMeta OBJECT variable_meta.cpp)

add_library(Variables OBJECT variables.cpp)

