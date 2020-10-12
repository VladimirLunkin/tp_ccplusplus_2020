#include "music.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    const char *path_file = argv[1];

    size_t num = 0;
    music_track *track_library = create_track_library(path_file, &num);
    if (track_library == NULL) {
        return 1;
    }

    puts("Enter author name:");
    char author[SIZE_BUF];
    if (scanf("%s", author) != 1) {
        free_track_library(track_library, num);
        return 1;
    }
    print_tracks_by_author(track_library, num, author);

    free_track_library(track_library, num);

    return 0;
}
