#include "gtest/gtest.h"

#include <stdio.h>

extern "C" {
#include "music.h"
}

TEST(wrong_arguments, empty_path_file) {
    char *path_file = NULL;
    size_t num = 0;
    ASSERT_EQ(NULL, create_track_library(path_file, &num));
}

TEST(wrong_arguments, wrong_path_file) {
    const char *path_file = "wrong";
    size_t num = 0;
    ASSERT_EQ(NULL, create_track_library(path_file, &num));
}

TEST(wrong_arguments, wrong_file_format) {
    size_t num = 0;
    char path_file[] = "../tests/data/wrong_file_formatx";
    for (char i = '1'; i <= '3'; ++i) {
        path_file[strlen(path_file) - 1] = i;
        ASSERT_EQ(NULL, create_track_library(path_file, &num));
    }
}
