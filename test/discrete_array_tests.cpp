
#include <Philote/array.h>
#include <gtest/gtest.h>

#include <iostream>

using namespace philote;

// Test the constructor.
TEST(DiscreteArrayTests, Constructor)
{
    // create a 3-dimensional array
    DiscArray array = DiscArray({3, 4, 2});

    // check the shape of the array
    auto shape = array.Shape();

    // Expect equality.
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 4);
    EXPECT_EQ(shape[2], 2);
}

// Test the segment function.
TEST(DiscreteArrayTests, Segment)
{
    // create a 2-dimensional array
    DiscArray array = DiscArray({2, 2});

    // assign some data
    std::vector<long> data = {1, 2, 3, 4};
    array.Segment(0, 3, data);

    // now replace only the middle values
    std::vector<long> data_seg = {1, 2};
    array.Segment(1, 2, data_seg);

    // check the element (0,0)
    EXPECT_EQ(array(0), 1);

    // check the element (0,1)
    EXPECT_EQ(array(1), 1);

    // check the element (1,0)
    EXPECT_EQ(array(2), 2);

    // check the element (1,1)
    EXPECT_EQ(array(3), 4);

    // now replace only the last value (to see if single values can be set)
    data_seg = {1};
    array.Segment(3, 3, data_seg);

    // check the element (0,0)
    EXPECT_EQ(array(0), 1);

    // check the element (0,1)
    EXPECT_EQ(array(1), 1);

    // check the element (1,0)
    EXPECT_EQ(array(2), 2);

    // check the element (1,1)
    EXPECT_EQ(array(3), 1);
}

// Test the size function.
TEST(DiscreteArrayTests, Size)
{
    // create a 3-dimensional array
    DiscArray array = DiscArray({3, 4, 2});

    // check the shape of the array
    auto size = array.Size();

    EXPECT_EQ(size, 24);
}

// Test the shape function.
TEST(DiscreteArrayTests, Shape)
{
    // create a 3-dimensional array
    DiscArray array = DiscArray({3, 4, 2});

    // check the shape of the array
    auto shape = array.Shape();

    // Expect equality.
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 4);
    EXPECT_EQ(shape[2], 2);
}

// Test the element retrieval operator.
TEST(DiscreteArrayTests, ElementRetrieval)
{
    // create a 2-dimensional array
    DiscArray array = DiscArray({2, 2});

    // assign some data
    std::vector<long> data = {1, 2, 3, 4};
    array.Segment(0, 3, data);

    // check the element (0,0)
    EXPECT_EQ(array(0), 1);

    // check the element (0,1)
    EXPECT_EQ(array(1), 2);

    // check the element (1,0)
    EXPECT_EQ(array(2), 3);

    // check the element (1,1)
    EXPECT_EQ(array(3), 4);
}