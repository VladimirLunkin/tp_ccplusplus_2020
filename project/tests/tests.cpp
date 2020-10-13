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

    free_track(&track2);
    fclose(fptr);
}

TEST(logic_test, print_track_info) {
    const char *path_output_file = "../tests/tmp/test1";
    FILE *fptr = fopen(path_output_file, "a+");
    if (fptr == NULL) {
        FAIL();
    }

    music_track track1 = {"Aa", "Bb", "Cc", 1};
    music_track track2;
    int pos = ftell(fptr);
    print_track_info(fptr, &track1);

    fseek(fptr, pos, SEEK_SET);
    if (read_track_info(fptr, &track2)) {
        fclose(fptr);
        FAIL();
    }

    ASSERT_STREQ(track1.author, track2.author);
    ASSERT_STREQ(track1.performer, track2.performer);
    ASSERT_STREQ(track1.name, track2.name);
    ASSERT_EQ(track1.duration, track2.duration);

    free_track(&track2);
    fclose(fptr);
}
