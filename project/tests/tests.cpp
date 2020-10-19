#include "gtest/gtest.h"

extern "C" {
#include "test.h"  // NOLINT
}

TEST(tests, test) {
    ASSERT_TRUE(true);
}
