
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

# add array tests
add_executable(ArrayTests array_tests.cpp)
target_link_libraries(ArrayTests PhiloteCpp)
target_link_libraries(ArrayTests GTest::gtest_main)
gtest_discover_tests(ArrayTests)