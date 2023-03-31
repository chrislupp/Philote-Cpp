
cmake_minimum_required (VERSION 3.9)


project(PhiloteCpp
    VERSION 0.1.0
)

# cache option variables
set(
    BUILD_TESTS
    FALSE
    CACHE BOOL "Build unit tests"
    )

# add cmake scripts
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)



# Find gRPC and its dependencies
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# add include directories
include_directories(${Protobuf_INCLUDE_DIR})
include_directories(${_GRPC_GRPCPP_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})


# add subdirectories
add_subdirectory(src)


if (BUILD_TESTS)
    message("Building with tests.")

    enable_testing()
    find_package(GTest REQUIRED)
    include(GoogleTest)
    add_subdirectory(test)
endif (BUILD_TESTS)