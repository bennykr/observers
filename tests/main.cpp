#include "gtest/gtest.h"
#include "subject_base.hpp"
#include "observer_base.hpp"

#include <string>

using namespace observers;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::GTEST_FLAG(filter) = "*FILTER*";
    return RUN_ALL_TESTS();
}