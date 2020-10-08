#include "music.h"

#include <string.h>


music_track* create_track_library(const char *path_file, size_t *num) {
    if (path_file == NULL) {
        return NULL;
    }

    FILE *fptr = fopen(path_file, "r");
    if (fptr == NULL) {
        printf("Неверный путь: %s\n", path_file);
        return NULL;
    }

    if (fscanf(fptr, "%ld", num) != 1) {
        fclose(fptr);
        return NULL;
    }

    music_track *track_library = (music_track*)malloc(*num * sizeof(music_track));
    if (track_library == NULL) {
        fclose(fptr);
        return NULL;
    }

    for (size_t i = 0; i < *num; ++i) {
        if (fscanf(fptr, "%s%s%s%d",
            track_library[i].author,
            track_library[i].performer,
            track_library[i].name,
            &track_library[i].duration) != 4) {
            fclose(fptr);
            return NULL;
        }
    }
    fclose(fptr);
    return track_library;
}

int print_tracks_by_author(music_track *track_library, const size_t num, const char *author) {
    if (track_library == NULL || author == NULL) {
        return 1;
    }
    size_t count = 0;
    for (size_t i = 0; i < num; ++i) {
        if (strcmp(author, track_library[i].author) == 0) {
            print_track_info(&track_library[i]);
            count++;
        }
    }
    if (count == 0) {
        printf("%s\n", "author not found");
    }
    return 0;
}

void print_track_info(music_track *track) {
    printf("%s\t%s\t%s\t%d\n",
        track->author,
        track->performer,
        track->name,
        track->duration);
}

int free_track_library(music_track *track_library) {
    if (track_library == NULL) {
        return 1;
    }
    free(track_library);
    return 0;
}
