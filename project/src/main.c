#include "music.h"  // NOLINT


int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    const char *path_input_file = argv[1];
    const char *path_output_file = argv[2];

    size_t num = 0;
    music_track *track_lib = create_track_library(path_input_file, &num);
    if (track_lib == NULL) {
        return 1;
    }

    puts("Enter author name:");
    char author[SIZE_BUF];
    if (scanf("%63s", author) != 1) {
        free_track_library(track_lib, num);
        return 1;
    }
    print_tracks_by_author(path_output_file, track_lib, num, author);

    free_track_library(track_lib, num);

    return 0;
}
