#include "gtest/gtest.h"


extern "C" {
#include "music.h"  // NOLINT
}

void cmp_track(const music_track &track1, const music_track &track2) {
    ASSERT_STREQ(track1.author, track2.author);
    ASSERT_STREQ(track1.performer, track2.performer);
    ASSERT_STREQ(track1.name, track2.name);
    ASSERT_EQ(track1.duration, track2.duration);
}

void cmp_file(const char *path_output_file, const char *path_result_file) {
    FILE *fptr_out = fopen(path_output_file, "rt");
    FILE *fptr_res = fopen(path_result_file, "rt");
    if (fptr_out == nullptr || fptr_res == nullptr) {
        FAIL();
    }

    size_t num1;
    size_t num2;
    if (fscanf(fptr_out, "%zu", &num1) != 1 ||
        fscanf(fptr_res, "%zu", &num2) != 1 ||
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
        cmp_track(track1, track2);
        free_track(&track1);
        free_track(&track2);
    }

    fclose(fptr_out);
    fclose(fptr_res);
}

void test_main(const char *path_input_file, const char *path_output_file,
               const char *author, const char *path_result_file) {
    size_t num = 0;
    music_track *track_lib = create_track_library(path_input_file, &num);
    if (track_lib == nullptr) {
        FAIL();
    }
    print_tracks_by_author(path_output_file, track_lib, num, author);
    free_track_library(track_lib, num);

    cmp_file(path_output_file, path_result_file);
}

TEST(test_func, read_track_info) {
    const char *path_input_file = "../tests/data/track_info";
    FILE *fptr = fopen(path_input_file, "rt");
    if (fptr == nullptr) {
        FAIL();
    }

    music_track track1 = {"Aa", "Bb", "Cc", 1};
    music_track track2;
    if (read_track_info(fptr, &track2)) {
        FAIL();
    }

    cmp_track(track1, track2);

    free_track(&track2);
    fclose(fptr);
}

TEST(test_func, print_track_info) {
    const char *path_output_file = "../tests/tmp/print_track_info/test1";
    FILE *fptr = fopen(path_output_file, "w+");
    if (fptr == nullptr) {
        FAIL();
    }

    music_track track1 = {"Aa", "Bb", "Cc", 1};
    music_track track2;
    int pos = ftell(fptr);
    print_track_info(fptr, &track1);

    fseek(fptr, pos, SEEK_SET);
    if (read_track_info(fptr, &track2)) {
        FAIL();
    }

    cmp_track(track1, track2);

    free_track(&track2);
    fclose(fptr);
}

TEST(logic_test, test1) {
    const char *path_input_file = "../tests/data/lib1";
    const char *path_output_file = "../tests/tmp/logic_test/test1";
    const char *path_result_file = "../tests/result/logic_test/test1";
    const char *authors = "Хаски";

    test_main(path_input_file, path_output_file, authors, path_result_file);
}

TEST(logic_test, test2) {
    const char *path_input_file = "../tests/data/lib1";
    const char *path_output_file = "../tests/tmp/logic_test/test2";
    const char *path_result_file = "../tests/result/logic_test/test2";
    const char *authors = "";

    test_main(path_input_file, path_output_file, authors, path_result_file);
}

TEST(logic_test, test3) {
    const char *path_input_file = "../tests/data/lib2";
    const char *path_output_file = "../tests/tmp/logic_test/test3";
    const char *path_result_file = "../tests/result/logic_test/test3";
    const char *authors = "a";

    test_main(path_input_file, path_output_file, authors, path_result_file);
}

TEST(logic_test, test4) {
    const char *path_input_file = "../tests/data/lib2";
    const char *path_output_file = "../tests/tmp/logic_test/test4";
    const char *path_result_file = "../tests/result/logic_test/test4";
    const char *authors = "AAAAAAAAAA";

    test_main(path_input_file, path_output_file, authors, path_result_file);
}

TEST(logic_test, test5) {
    const char *path_input_file = "../tests/data/lib2";
    const char *path_output_file = "../tests/tmp/logic_test/test5";
    const char *path_result_file = "../tests/result/logic_test/test5";
    const char *authors = "no_author";

    test_main(path_input_file, path_output_file, authors, path_result_file);
}
