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
    const char *path_file = "/home/vladimir/Документы/tp_ccplusplus_2020/project/tests/data/wrong_file_format1";
    ASSERT_EQ(NULL, create_track_library(path_file, &num));

    path_file = "/home/vladimir/Документы/tp_ccplusplus_2020/project/tests/data/wrong_file_format2";
    ASSERT_EQ(NULL, create_track_library(path_file, &num));

    path_file = "/home/vladimir/Документы/tp_ccplusplus_2020/project/tests/data/wrong_file_format3";
    ASSERT_EQ(NULL, create_track_library(path_file, &num));
}
