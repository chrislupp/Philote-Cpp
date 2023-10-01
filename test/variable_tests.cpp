/*
    Philote C++ Bindings

    Copyright 2022-2023 Christopher A. Lupp

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#include <Philote/variable.h>
#include <gtest/gtest.h>

#include <iostream>

using namespace philote;

// Test the constructor.
TEST(VariableTests, Constructor)
{
    // create a 3-dimensional array
    Variable array = Variable(kInput, {3, 4, 2});

    // check the shape of the array
    auto shape = array.Shape();

    // Expect equality.
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 4);
    EXPECT_EQ(shape[2], 2);
}

// Test the segment function.
TEST(VariableTests, Segment)
{
    // create a 2-dimensional array
    Variable array = Variable(kInput, {2, 2});

    // assign some data
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0};
    array.Segment(0, 3, data);

    // now replace only the middle values
    std::vector<double> data_seg = {1.0, 2.0};
    array.Segment(1, 2, data_seg);

    // check the element (0,0)
    EXPECT_EQ(array(0), 1.0);

    // check the element (0,1)
    EXPECT_EQ(array(1), 1.0);

    // check the element (1,0)
    EXPECT_EQ(array(2), 2.0);

    // check the element (1,1)
    EXPECT_EQ(array(3), 4.0);

    // now replace only the last value (to see if single values can be set)
    data_seg = {1.0};
    array.Segment(3, 3, data_seg);

    // check the element (0,0)
    EXPECT_EQ(array(0), 1.0);

    // check the element (0,1)
    EXPECT_EQ(array(1), 1.0);

    // check the element (1,0)
    EXPECT_EQ(array(2), 2.0);

    // check the element (1,1)
    EXPECT_EQ(array(3), 1.0);
}

// Test the size function.
TEST(VariableTests, Size)
{
    // create a 3-dimensional array
    Variable array = Variable(kInput, {3, 4, 2});

    // check the shape of the array
    auto size = array.Size();

    EXPECT_EQ(size, 24);
}

// Test the shape function.
TEST(VariableTests, Shape)
{
    // create a 3-dimensional array
    Variable array = Variable(kInput, {3, 4, 2});

    // check the shape of the array
    auto shape = array.Shape();

    // Expect equality.
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 4);
    EXPECT_EQ(shape[2], 2);
}

// Test the element retrieval operator.
TEST(VariableTests, ElementRetrieval)
{
    // create a 2-dimensional array
    Variable array = Variable(kInput, {2, 2});

    // assign some data
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0};
    array.Segment(0, 3, data);

    // check the element (0,0)
    EXPECT_EQ(array(0), 1.0);

    // check the element (0,1)
    EXPECT_EQ(array(1), 2.0);

    // check the element (1,0)
    EXPECT_EQ(array(2), 3.0);

    // check the element (1,1)
    EXPECT_EQ(array(3), 4.0);
}

// Test the element retrieval operator.
TEST(VariableTests, Chunking)
{
    // create a 2-dimensional array
    Variable array = Variable(kInput, {2, 2});

    // assign some data
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0};
    array.Segment(0, 3, data);

    // check the element (0,0)
    EXPECT_EQ(array(0), 1.0);

    // check the element (0,1)
    EXPECT_EQ(array(1), 2.0);

    // check the element (1,0)
    EXPECT_EQ(array(2), 3.0);

    // check the element (1,1)
    EXPECT_EQ(array(3), 4.0);
}