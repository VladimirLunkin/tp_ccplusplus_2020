#ifndef PROJECT_INCLUDE_MUSIC_H_
#define PROJECT_INCLUDE_MUSIC_H_

#include <stdio.h>
#include <stdlib.h>

#define SIZE_BUF 64


typedef struct {
    char *author;
    char *performer;
    char *name;
    int duration;
} music_track;

int read_track_info(FILE *fptr, music_track *track);
int print_track_info(FILE *fptr, music_track *track);
void free_track(music_track *track);

music_track* create_track_library(const char *path_input_file, size_t *num);
int print_tracks_by_author(const char *path_output_file, music_track *track_lib,
                           const size_t num, const char *author);
void free_track_library(music_track *track_lib, const size_t num);

#endif  //  PROJECT_INCLUDE_MUSIC_H_
