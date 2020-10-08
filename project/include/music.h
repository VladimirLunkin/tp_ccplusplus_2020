#ifndef PROJECT_INCLUDE_MUSIC_H
#define PROJECT_INCLUDE_MUSIC_H

#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 20


typedef struct {
    char author[STR_LEN];
    char performer[STR_LEN];
    char name[STR_LEN];
    int duration;
} music_track;

music_track* create_track_library(const char *path_file, size_t *num);
int print_tracks_by_author(music_track *track_library, const size_t num, const char *author);
void print_track_info(music_track *track);
int free_track_library(music_track *track_library);

#endif  //  PROJECT_INCLUDE_MUSIC_H
