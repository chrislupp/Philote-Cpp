

# generate gRPC stubs
#--------------------

# Set the path to the directory where you want to generate the C++ headers
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set the path to the directory containing the .proto files
set(PROTO_DIR ${CMAKE_SOURCE_DIR}/proto)

# Set the paths to your .proto files
set(PROTO_FILES array.proto explicit.proto metadata.proto options.proto)


# Combine the two lists element-wise
set(PROTO_FILES_DEPEND "")

foreach(elem ${PROTO_FILES})
    string(REPLACE ".proto" "" file_no_ext ${elem})
    list(APPEND PROTO_FILES_DEPEND ${CMAKE_SOURCE_DIR}/proto/${elem})
    list(APPEND PROTO_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${file_no_ext}.pb.h)
    list(APPEND PROTO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${file_no_ext}.pb.cc)
endforeach()

# Add a custom target to generate the C++ headers from the .proto files using
add_custom_command(
    OUTPUT ${PROTO_HEADERS} ${PROTO_SRC}
    COMMAND protobuf::protoc
        --proto_path=${PROTO_DIR}
        --grpc_out=${GENERATED_DIR}
        --cpp_out=${GENERATED_DIR}
        ${PROTO_FILES}
    # WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/proto
    DEPENDS ${PROTO_FILES_DEPEND}
    COMMENT "Generating C++ stubs from protobuf files" 
    VERBATIM
)


# create targets for the generated source so it can be used with other targets
add_library(GrpcGenerated OBJECT ${PROTO_HEADERS} ${PROTO_SRC})

target_link_libraries(GrpcGenerated PRIVATE protobuf::libprotobuf gRPC::grpc++)