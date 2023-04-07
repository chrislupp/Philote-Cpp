
# array tests
add_executable(ArrayTests array_tests.cpp)
target_link_libraries(ArrayTests PhiloteCpp)
target_link_libraries(ArrayTests GTest::gtest_main)
gtest_discover_tests(ArrayTests)

# discrete array tests
add_executable(DiscreteArrayTests discrete_array_tests.cpp)
target_link_libraries(DiscreteArrayTests PhiloteCpp)
target_link_libraries(DiscreteArrayTests GTest::gtest_main)
gtest_discover_tests(DiscreteArrayTests)

# # explicit server
# add_executable(DiscreteArrayTests discrete_array_tests.cpp)
# target_link_libraries(DiscreteArrayTests PhiloteCpp)
# target_link_libraries(DiscreteArrayTests GTest::gtest_main)
# gtest_discover_tests(DiscreteArrayTests)

# # explicit client
# add_executable(DiscreteArrayTests discrete_array_tests.cpp)
# target_link_libraries(DiscreteArrayTests PhiloteCpp)
# target_link_libraries(DiscreteArrayTests GTest::gtest_main)
# gtest_discover_tests(DiscreteArrayTests)

# # implicit server
# add_executable(DiscreteArrayTests discrete_array_tests.cpp)
# target_link_libraries(DiscreteArrayTests PhiloteCpp)
# target_link_libraries(DiscreteArrayTests GTest::gtest_main)
# gtest_discover_tests(DiscreteArrayTests)

# # implicit client
# add_executable(DiscreteArrayTests discrete_array_tests.cpp)
# target_link_libraries(DiscreteArrayTests PhiloteCpp)
# target_link_libraries(DiscreteArrayTests GTest::gtest_main)
# gtest_discover_tests(DiscreteArrayTests)