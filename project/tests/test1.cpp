#include <stdio.h>

#include "gtest/gtest.h"


extern "C" {
#include "music.h"  // NOLINT
}

TEST(wrong_arguments, empty_path_file) {
    const char *path_file = nullptr;
    size_t num = 0;
    ASSERT_EQ(nullptr, create_track_library(path_file, &num));
}

TEST(wrong_arguments, wrong_path_file) {
    const char *path_file = "wrong";
    size_t num = 0;
    ASSERT_EQ(nullptr, create_track_library(path_file, &num));
}

TEST(wrong_arguments, wrong_file_format) {
    size_t num = 0;
    char path_file[] = "../tests/data/wrong_file_formatx";
    for (char i = '1'; i <= '3'; ++i) {
        path_file[strlen(path_file) - 1] = i;
        music_track *track_lib = create_track_library(path_file, &num);
        ASSERT_EQ(nullptr, track_lib);
    }
}

TEST(wrong_arguments, read_track) {
    FILE *fptr = nullptr;
    music_track *track = nullptr;
    ASSERT_EQ(1, read_track_info(fptr, track));
}

TEST(wrong_arguments, print_tracks_by_author) {
    const char *path_output_file = nullptr;
    music_track *track_lib = nullptr;
    size_t num = 0;
    char *author = nullptr;
    ASSERT_EQ(1,
              print_tracks_by_author(path_output_file, track_lib, num, author));
}

TEST(wrong_arguments, print_track_info) {
    FILE *fptr = nullptr;
    music_track *track = nullptr;
    ASSERT_EQ(1, print_track_info(fptr, track));
}
