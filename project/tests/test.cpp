#include "gtest/gtest.h"

#include <stdio.h>

extern "C" {
#include "music.h"
}

TEST(wrong_arguments, empty_path_file) {
    const char *path_file = NULL;
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
        music_track *track_library = create_track_library(path_file, &num);
        ASSERT_EQ(NULL, track_library);
    }
}

TEST(wrong_arguments, read_track) {
    FILE *fptr = NULL;
    music_track *track = NULL;
    ASSERT_EQ(1, read_track_info(fptr, track));
}

TEST(wrong_arguments, print_tracks_by_author) {
    const char *path_output_file = NULL;
    music_track *track_library = NULL;
    size_t num = 0;
    char *author = NULL;
    ASSERT_EQ(1, print_tracks_by_author(path_output_file, track_library, num, author));
}

TEST(wrong_arguments, print_track_info) {
    FILE *fptr = NULL;
    music_track *track = NULL;
    ASSERT_EQ(1, print_track_info(fptr, track));
}
