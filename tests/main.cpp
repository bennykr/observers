#include "gtest/gtest.h"
#include "subject.hpp"


using namespace observers;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::GTEST_FLAG(filter) = "*FILTER*";
    return RUN_ALL_TESTS();
}

class A : public Subject{};

TEST(TITLE, SUBTITLE) {
    A a;
    a.f();
    ASSERT_EQ(1, 1);
}