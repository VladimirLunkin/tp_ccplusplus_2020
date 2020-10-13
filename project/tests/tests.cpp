#include "gtest/gtest.h"

extern "C" {
#include "music.h"
}

TEST(logic_test, read_track_info) {
    const char *path_input_file = "../tests/data/track_info";
    FILE *fptr = fopen(path_input_file, "rt");
    if (fptr == NULL) {
        FAIL();
    }

    music_track track1 = {"Aa", "Bb", "Cc", 1};
    music_track track2;
    if (read_track_info(fptr, &track2)) {
        fclose(fptr);
        FAIL();
    }

    ASSERT_STREQ(track1.author, track2.author);
    ASSERT_STREQ(track1.performer, track2.performer);
    ASSERT_STREQ(track1.name, track2.name);
    ASSERT_EQ(track1.duration, track2.duration);

    fclose(fptr);
}


//
//TEST(logic_test, print_track_info) {
//    music_track *track = {"Aa", "Bb", "Cc", 1};
//    const char *path_output_file = "../tests/tmp/test1";
//    FILE *fptr = fopen(path_output_file, "a+");
//    if (fptr == NULL) {
//        FAIL();
//    }
//
//    print_track_info(fptr, track);
//
//
//}
//
//TEST(logic_test, create_track_library) {
//    const char *path_input_file = argv[1];
//    const char *path_output_file = argv[2];
//
//    size_t num = 0;
//    music_track *track_library = create_track_library(path_input_file, &num);
//    if (track_library == NULL) {
//        FAIL();
//    }
//
//    puts("Enter author name:");
//    char author[SIZE_BUF];
//    if (scanf("%s", author) != 1) {
//        free_track_library(track_library, num);
//        FAIL();
//    }
//    print_tracks_by_author(path_output_file, track_library, num, author);
//
//    free_track_library(track_library, num);
//}
