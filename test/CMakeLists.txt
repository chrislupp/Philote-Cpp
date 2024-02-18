#===============================================================================
#    Philote C++ Bindings
#
#    Copyright 2022-2024 Christopher A. Lupp
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
#
#    This work has been cleared for public release, distribution unlimited, case
#    number: AFRL-2023-5716.
#
#    The views expressed are those of the authors and do not reflect the
#    official guidance or position of the United States Government, the
#    Department of Defense or of the United States Air Force.
#
#    Statement from DoD: The Appearance of external hyperlinks does not
#    constitute endorsement by the United States Department of Defense (DoD) of
#    the linked websites, of the information, products, or services contained
#    therein. The DoD does not exercise any editorial, security, or other
#    control over the information you may find at these locations.
#===============================================================================

# array tests
add_executable(VariableTests variable_tests.cpp)
target_link_libraries(VariableTests PhiloteCpp GTest::gtest_main GTest::gmock protobuf::libprotobuf gRPC::grpc++)
gtest_discover_tests(VariableTests)

# discipline server tests
add_executable(DisciplineServerTests discipline_server_tests.cpp)
target_link_libraries(DisciplineServerTests PhiloteCpp GTest::gtest_main GTest::gmock protobuf::libprotobuf gRPC::grpc++)
gtest_discover_tests(DisciplineServerTests)

# discipline client tests
add_executable(DisciplineClientTests discipline_client_tests.cpp)
target_link_libraries(DisciplineClientTests PhiloteCpp GTest::gtest_main GTest::gmock protobuf::libprotobuf gRPC::grpc++)
gtest_discover_tests(DisciplineClientTests)

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