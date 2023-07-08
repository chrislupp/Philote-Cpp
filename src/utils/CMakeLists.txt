
add_library(Array OBJECT array.cpp)
target_compile_definitions(Array PRIVATE TYPE=double)

add_library(DiscreteArray OBJECT array.cpp)
target_compile_definitions(DiscreteArray PRIVATE TYPE=int64_t)

add_library(VariableMeta OBJECT variable_meta.cpp)

add_library(Variables OBJECT variables.cpp)

add_library(Partials OBJECT partials.cpp)
