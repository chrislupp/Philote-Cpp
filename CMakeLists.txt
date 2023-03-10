
cmake_minimum_required (VERSION 3.9)


project(PhiloteCpp
    VERSION 0.1.0
)

# add cmake scripts
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


# find required packages


# add include directories
include_directories(.)


# add subdirectories
add_subdirectory(src)