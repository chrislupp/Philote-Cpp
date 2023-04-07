
#include <Philote/array.hpp>
#include <gtest/gtest.h>

#include <iostream>

// Test the constructor.
TEST(ArrayTests, Constructor)
{
    // create a 3-dimensional array
    Array array = Array({3, 4, 2});

    // check the shape of the array
    auto shape = array.Shape();

    // Expect equality.
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 4);
    EXPECT_EQ(shape[2], 2);
}

// Test the segment function.
TEST(ArrayTests, Segment)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

// Test the size function.
TEST(ArrayTests, Size)
{
    // create a 3-dimensional array
    Array array = Array({3, 4, 2});

    // check the shape of the array
    auto size = array.Size();

    EXPECT_EQ(size, 24);
}

// Test the shape function.
TEST(ArrayTests, Shape)
{
    // create a 3-dimensional array
    Array array = Array({3, 4, 2});

    // check the shape of the array
    auto shape = array.Shape();

    // Expect equality.
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 4);
    EXPECT_EQ(shape[2], 2);
}

// Test the element retrieval operator.
TEST(ArrayTests, ElementRetrieval)
{
    // create a 2-dimensional array
    Array array = Array({2, 2});

    // assign some data
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0};
    array.Segment(0, 4, data);

    // check the element (0,0)
    EXPECT_EQ(array(0), 1.0);

    // check the element (0,1)
    EXPECT_EQ(array(1), 2.0);

    // check the element (1,0)
    EXPECT_EQ(array(2), 3.0);

    // check the element (1,1)
    EXPECT_EQ(array(3), 4.0);
}