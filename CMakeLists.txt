#===============================================================================
#    Philote C++ Bindings
#
#    Copyright 2022-2023 Christopher A. Lupp
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#===============================================================================
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
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# add include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/generated)


# add subdirectories
add_subdirectory(generated)
add_subdirectory(src)
add_subdirectory(examples)



if (BUILD_TESTS)
    message("Building with tests.")

    enable_testing()
    find_package(GTest REQUIRED)
    include(GoogleTest)
    add_subdirectory(test)
endif (BUILD_TESTS)