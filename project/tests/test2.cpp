#include "gtest/gtest.h"

#include <fstream>

extern "C" {
#include "music.h"
}

void track_cmp(music_track &track1, music_track &track2) {
    ASSERT_STREQ(track1.author, track2.author);
    ASSERT_STREQ(track1.performer, track2.performer);
    ASSERT_STREQ(track1.name, track2.name);
    ASSERT_EQ(track1.duration, track2.duration);
}

TEST(logic_test, read_track_info) {
    const char *path_input_file = "../tests/data/track_info";
    FILE *fptr = fopen(path_input_file, "rt");
    if (fptr == nullptr) {
        FAIL();
    }

    music_track track1 = {"Aa", "Bb", "Cc", 1};
    music_track track2;
    if (read_track_info(fptr, &track2)) {
        fclose(fptr);
        FAIL();
    }

    track_cmp(track1, track2);

    free_track(&track2);
    fclose(fptr);
}

TEST(logic_test, print_track_info) {
    const char *path_output_file = "../tests/tmp/print_track_info/test1";
    FILE *fptr = fopen(path_output_file, "a+");
    if (fptr == nullptr) {
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

    track_cmp(track1, track2);

    free_track(&track2);
    fclose(fptr);
}

TEST(logic_test, create_track_library) {
    char path_input_file[] = "../tests/data/libx";
    char path_output_file[] = "../tests/tmp/create_track_library/testx";
    char path_result_file[] = "../tests/result/create_track_library/testx";
    char *authors[] = {"Хаски", "a"};

    char num_test;
    size_t k;
    for (num_test = '1', k = 0; k < 2; ++num_test, ++k) {
        path_input_file[strlen(path_input_file) - 1] = num_test;
        path_output_file[strlen(path_output_file) - 1] = num_test;
        path_result_file[strlen(path_result_file) - 1] = num_test;
        const char *author = authors[k];

        size_t num = 0;
        music_track *track_library = create_track_library(path_input_file, &num);
        if (track_library == nullptr) {
            FAIL();
        }
        print_tracks_by_author(path_output_file, track_library, num, author);
        free_track_library(track_library, num);

        FILE *fptr_out = fopen(path_output_file, "rt");
        FILE *fptr_res = fopen(path_result_file, "rt");
        if (fptr_out == nullptr || fptr_res == nullptr) {
            FAIL();
        }

        size_t num1;
        size_t num2;
        if (fscanf(fptr_out, "%ld", &num1) != 1 ||
            fscanf(fptr_res, "%ld", &num2) != 1 ||
            num1 != num2) {
            fclose(fptr_out);
            fclose(fptr_res);
            FAIL();
        }
        for (size_t i = 0; i < num1; ++i) {
            music_track track1;
            music_track track2;
            if (read_track_info(fptr_out, &track1) ||
                read_track_info(fptr_res, &track2)) {
                free_track(&track1);
                free_track(&track2);
                fclose(fptr_out);
                fclose(fptr_res);
                FAIL();
            }
            track_cmp(track1, track2);
            free_track(&track1);
            free_track(&track2);
        }

        fclose(fptr_out);
        fclose(fptr_res);
    }
}
