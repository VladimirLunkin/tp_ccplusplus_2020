#include "music.h"  // NOLINT

#include <string.h>


int read_track_info(FILE *fptr, music_track *track) {
    if (fptr == NULL || track == NULL) {
        return 1;
    }

    char buf[3][SIZE_BUF];
    if (fscanf(fptr, "%63s%63s%63s%d",
               buf[0],
               buf[1],
               buf[2],
               &track->duration) != 4) {
        return 1;
    }

    track->author = (char*)malloc((strlen(buf[0]) + 1) * sizeof(char));
    track->performer = (char*)malloc((strlen(buf[1]) + 1) * sizeof(char));
    track->name = (char*)malloc((strlen(buf[2]) + 1) * sizeof(char));
    if (track->author == NULL ||
        track->performer == NULL ||
        track->name == NULL) {
        free(track->author);
        free(track->performer);
        free(track->name);
        return 1;
    }

    if (snprintf(track->author, SIZE_BUF, "%s", buf[0]) < 1 ||
        snprintf(track->performer, SIZE_BUF, "%s", buf[1]) < 1 ||
        snprintf(track->name, SIZE_BUF, "%s", buf[2]) < 1) {
        free(track->author);
        free(track->performer);
        free(track->name);
        return 1;
    }

    return 0;
}
int print_track_info(FILE *fptr, music_track *track) {
    if (fptr == NULL || track == NULL) {
        return 1;
    }

    fprintf(fptr, "%s\t%s\t%s\t%d\n",
            track->author,
            track->performer,
            track->name,
            track->duration);

    return 0;
}
void free_track(music_track *track) {
    free(track->author);
    free(track->performer);
    free(track->name);
}

music_track* create_track_library(const char *path_input_file, size_t *num) {
    if (path_input_file == NULL) {
        return NULL;
    }

    FILE *fptr = fopen(path_input_file, "rt");
    if (fptr == NULL) {
        return NULL;
    }

    if (fscanf(fptr, "%zu", num) != 1) {
        fclose(fptr);
        return NULL;
    }

    music_track *track_lib = (music_track*)malloc(*num * sizeof(music_track));
    if (track_lib == NULL) {
        fclose(fptr);
        return NULL;
    }

    char buf[3][SIZE_BUF];
    for (size_t i = 0; i < *num; ++i) {
        if (read_track_info(fptr, &track_lib[i])) {
            free_track_library(track_lib, i);
            fclose(fptr);
            return NULL;
        }
    }

    fclose(fptr);

    return track_lib;
}
int print_tracks_by_author(const char *path_output_file, music_track *track_lib,
                           const size_t num, const char *author) {
    if (track_lib == NULL || author == NULL) {
        return 1;
    }

    FILE *fptr = stdout;
    if (path_output_file != NULL) {
        fptr = fopen(path_output_file, "w");
    }
    if (fptr == NULL) {
        return 1;
    }

    size_t count = 0;
    for (size_t i = 0; i < num; ++i) {
        if (strcmp(author, track_lib[i].author) == 0) {
            count++;
        }
    }
    fprintf(fptr, "%zu\n", count);
    for (size_t i = 0; i < num; ++i) {
        if (strcmp(author, track_lib[i].author) == 0) {
            print_track_info(fptr, &track_lib[i]);
        }
    }

    fclose(fptr);

    return 0;
}
void free_track_library(music_track *track_lib, const size_t num) {
    for (size_t i = 0; i < num; ++i) {
        free_track(&track_lib[i]);
    }
    free(track_lib);
}
