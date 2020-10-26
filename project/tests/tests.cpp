#include "gtest/gtest.h"

extern "C" {
#include "consistently/character_series.h"
}

enum class ERROR {
    POPULAR_SERIES = -1,
    WRONG_ARG = 1,
};

TEST(wrong_arguments, create_sets_from_file_nullptr) {
    const char *path = nullptr;
    ASSERT_FALSE(create_sets_from_file(path));
}

TEST(wrong_arguments, create_sets_from_file_wrong_name) {
    const char *path = "wrong_file_name";
    ASSERT_FALSE(create_sets_from_file(path));
}

TEST(wrong_arguments, free_nullptr) {
    Sets *sets = nullptr;
    ASSERT_EQ(static_cast<int>(ERROR::WRONG_ARG), free_sets(sets));
}

TEST(wrong_arguments, sets_push_sets_nullptr) {
    Sets *sets = nullptr;
    Series series = {1, 'a', 1};
    ASSERT_EQ(static_cast<int>(ERROR::WRONG_ARG), sets_push(sets, &series));
}

TEST(wrong_arguments, sets_push_series_nullptr) {
    Sets *sets = create_sets();
    Series *series = nullptr;
    ASSERT_EQ(static_cast<int>(ERROR::WRONG_ARG), sets_push(sets, series));
    free_sets(sets);
}

TEST(wrong_arguments, sets_resize_nullptr) {
    Sets *sets = nullptr;
    ssize_t size = 0;
    ASSERT_EQ(static_cast<int>(ERROR::WRONG_ARG), sets_resize(sets, size));
}

TEST(wrong_arguments, popular_series_nullptr) {
    Sets *sets = nullptr;
    ASSERT_EQ(static_cast<int>(ERROR::POPULAR_SERIES), popular_series(sets));
}

TEST(wrong_arguments, print_series_nullptr) {
    const char *path = nullptr;
    Series *series = nullptr;
    ASSERT_EQ(static_cast<int>(ERROR::WRONG_ARG), print_series(path, series));
}

TEST(wrong_arguments, print_series_from_sets_nullptr) {
    const char *path = nullptr;
    Sets *sets = nullptr;
    ssize_t size = 0;
    ASSERT_EQ(static_cast<int>(ERROR::WRONG_ARG),
              print_series_from_sets(path, sets, size));
}

TEST(wrong_arguments, print_series_from_sets_error_ind) {
    const char path[] = SOURCE_DIR"/test_output/print_series_from_sets_error_ind";
    Sets *sets = create_sets_from_file(path);
    ssize_t ind = 0;
    ASSERT_EQ(static_cast<int>(ERROR::WRONG_ARG), print_series_from_sets(path, sets, ind));
    free_sets(sets);
}

TEST(test_func, create_sets_from_file) {
    const char path[] = SOURCE_DIR"/test_data/test1";
    Sets *sets = create_sets_from_file(path);
    ASSERT_TRUE(sets);
    free_sets(sets);
}

TEST(test_func, sets_push) {
    const char path[] = SOURCE_DIR"/test_data/test1";
    Sets *sets = create_sets_from_file(path);
    Series series = {1, 'a', 1};
    ASSERT_FALSE(sets_push(sets, &series));
    free_sets(sets);
}

TEST(test_func, sets_resize) {
    const char path[] = SOURCE_DIR"/test_data/test0";
    Sets *sets = create_sets_from_file(path);
    ssize_t resize = 100;
    ASSERT_FALSE(sets_resize(sets, resize));
    free_sets(sets);
}

TEST(test_func, popular_series) {
    const char path[] = SOURCE_DIR"/test_data/test1";
    Sets *sets = create_sets_from_file(path);
    ASSERT_FALSE(popular_series(sets));
    free_sets(sets);
}

// Написать ответы и проверять их в цикле
//TEST(logic_test, ) {
//    char path[] = SOURCE_DIR"/test_data/test0";
//    for (char i = '0'; i < '5'; ++i) {
//        path[strlen(path) - 1] = i;
//
//        Sets *sets = create_sets_from_file(path);
//        ASSERT_TRUE(popular_series(sets));
//        free_sets(sets);
//    }
//}
