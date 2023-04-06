
#include <Philote/array.hpp>
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(ArrayTests, Constructor)
{
    // create a 3 dimensional array
    Array array = Array({3, 4, 2});

    // check the shape of the array
    auto shape = array.Shape();

    // Expect equality.
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 4);
    EXPECT_EQ(shape[2], 2);
}

// Demonstrate some basic assertions.
TEST(ArrayTests, Segment)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

// Demonstrate some basic assertions.
TEST(ArrayTests, Size)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

// Demonstrate some basic assertions.
TEST(ArrayTests, Shape)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

// Demonstrate some basic assertions.
TEST(ArrayTests, ElementRetrieval)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}