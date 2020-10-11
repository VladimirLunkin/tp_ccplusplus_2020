#include "gtest/gtest.h"

extern "C" {
#include "music.h"
}

TEST(test_case_name, test_name) {
    ASSERT_EQ(1, 1) << "1 is not equal 0";
}

TEST(test_case_name2, test_name1) {
    ASSERT_EQ(1, check_test(1)) << "1 is not equal 0";
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
