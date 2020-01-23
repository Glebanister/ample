#include "gtest/gtest.h"
#include "Activity.h"

TEST(UselessTest, test1)
{
    EXPECT_EQ(1, 1);
    EXPECT_EQ(20, 20);
    EXPECT_EQ(100, 100);
}

TEST(UselessTest, test2)
{
    EXPECT_EQ(1, 1);
    EXPECT_EQ(20, 20);
    EXPECT_EQ(100, 100);
}

TEST(MyTest, test1)
{
    EXPECT_EQ(1, 1);
    EXPECT_EQ(20, 20);
    EXPECT_EQ(100, 100);
}

TEST(MyTest, test2)
{
    EXPECT_EQ(1, 1);
    EXPECT_EQ(20, 20);
    EXPECT_EQ(100, 100);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
