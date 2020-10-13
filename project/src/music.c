#include "music.h"

#include <string.h>


music_track* create_track_library(const char *path_input_file, size_t *num) {
    if (path_input_file == NULL) {
        return NULL;
    }

    FILE *fptr = fopen(path_input_file, "rt");
    if (fptr == NULL) {
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

    char buf[3][SIZE_BUF];
    for (size_t i = 0; i < *num; ++i) {
        if (read_track_info(fptr, &track_library[i])) {
            free_track_library(track_library, i);
            fclose(fptr);
            return NULL;
        }
    }
    
    fclose(fptr);

    return track_library;
}

int read_track_info(FILE *fptr, music_track *track) {
    if (fptr == NULL || track == NULL) {
        return 1;
    }

    char buf[3][SIZE_BUF];
    if (fscanf(fptr, "%s%s%s%d",
               buf[0],
               buf[1],
               buf[2],
               &track->duration) != 4) {
        return 1;
    }

    track->author = (char*)malloc((strlen(buf[0]) + 1) * sizeof(char));
    track->performer = (char*)malloc((strlen(buf[1]) + 1) * sizeof(char));
    track->name = (char*)malloc((strlen(buf[2]) + 1) * sizeof(char));
    if (track->author == NULL || track->performer == NULL || track->name == NULL) {
        free(track->author);
        free(track->performer);
        free(track->name);
        return 1;
    }

    strcpy(track->author, buf[0]);
    strcpy(track->performer, buf[1]);
    strcpy(track->name, buf[2]);

    return 0;
}

int print_tracks_by_author(const char *path_output_file, music_track *track_library, const size_t num, const char *author) {
    if (track_library == NULL || author == NULL) {
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
        if (strcmp(author, track_library[i].author) == 0) {
            print_track_info(fptr, &track_library[i]);
            count++;
        }
    }
    if (count == 0) {
        printf("%s\n", "author not found");
    }

    fclose(fptr);

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

int free_track_library(music_track *track_library, const size_t num) {
    for (size_t i = 0; i < num; ++i) {
        free(track_library[i].author);
        free(track_library[i].performer);
        free(track_library[i].name);
    }
    free(track_library);
    return 0;
}
