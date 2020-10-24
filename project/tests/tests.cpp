#include "gtest/gtest.h"

extern "C" {
#include "consistently/character_series.h"
}

TEST(wrong_arguments, create_sets_from_file_nullptr) {
    const char *path = nullptr;
    ASSERT_EQ(nullptr, create_sets_from_file(path));
}

TEST(wrong_arguments, create_sets_from_file_wrong_name) {
    const char *path = "wrong_file_name";
    ASSERT_EQ(nullptr, create_sets_from_file(path));
}

TEST(wrong_arguments, free_nullptr) {
    Sets *sets = nullptr;
    ASSERT_EQ(1, free_sets(sets));  // магическая константа
}

TEST(wrong_arguments, sets_push_sets_nullptr) {
    Sets *sets = nullptr;
    Series series = {1, 'a', 1};
    ASSERT_EQ(1, sets_push(sets, &series));  // магическая константа
}

TEST(wrong_arguments, sets_push_series_nullptr) {
    Sets *sets = create_sets();
    Series *series = nullptr;
    ASSERT_EQ(1, sets_push(sets, series));  // магическая константа
    free_sets(sets);
}

TEST(wrong_arguments, sets_resize_nullptr) {
    Sets *sets = nullptr;
    ssize_t size = 0;
    ASSERT_EQ(1, sets_resize(sets, size));  // магическая константа
}

TEST(wrong_arguments, popular_series_nullptr) {
    Sets *sets = nullptr;
    ASSERT_EQ(-1, popular_series(sets));  // магическая константа
}

TEST(wrong_arguments, print_series_nullptr) {
    Series *series = nullptr;
    ASSERT_EQ(1, print_series(series));  // магическая константа
}

TEST(wrong_arguments, print_series_from_sets_nullptr) {
    Sets *sets = nullptr;
    ssize_t size = 0;
    ASSERT_EQ(1, print_series_from_sets(sets, size));  // магическая константа
}

TEST(wrong_arguments, print_series_from_sets_error_ind) {
    Sets *sets = create_sets();
    ssize_t ind = 0;
    ASSERT_EQ(1, print_series_from_sets(sets, ind));  // магическая константа
    free_sets(sets);
}
