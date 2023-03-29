

# generate gRPC stubs
#--------------------

# Set the paths to your .proto files
set(PROTO_FILES array.proto explicit.proto metadata.proto options.proto)

# Combine the two lists element-wise
set(PROTO_FILES_DEPEND "")
foreach(elem ${PROTO_FILES})
    list(APPEND PROTO_FILES_DEPEND ${CMAKE_SOURCE_DIR}/proto/${elem})
endforeach()

# Set the path to the directory where you want to generate the C++ headers
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set the path to the directory containing the .proto files
set(PROTO_DIR ${CMAKE_SOURCE_DIR}/proto)


# Add a custom target to generate the C++ headers from the .proto files using
# protoc
add_custom_target(
    generate_proto_headers ALL
    COMMAND protoc --cpp_out=${GENERATED_DIR} ${PROTO_FILES}
    DEPENDS ${PROTO_FILES_DEPEND}
    WORKING_DIRECTORY ${PROTO_DIR}
    COMMENT "Generating C++ headers from protobuf files"
    VERBATIM
)


# add the grpc generated headers to the include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


# create targets for the generated source so it can be used with other targets
add_library(ArrayGrpc OBJECT array.pb.cc)
set_property(TARGET ArrayGrpc PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(MetaDataGrpc OBJECT metadata.pb.cc)
set_property(TARGET MetaDataGrpc PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(OptionsGrpc OBJECT options.pb.cc)
set_property(TARGET OptionsGrpc PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_library(ExplicitGrpc OBJECT explicit.pb.cc)
set_property(TARGET ExplicitGrpc PROPERTY POSITION_INDEPENDENT_CODE TRUE)