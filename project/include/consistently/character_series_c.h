#ifndef PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_C_H_
#define PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_C_H_

#define INIT_NUMBER_SERIES 10

#include <stdlib.h>

typedef struct {
    int64_t length;
    char symbol;
    int64_t quantity;
} Series;

struct Sets;
typedef struct Sets Sets;

Sets *create_sets();
Sets *create_sets_from_file(const char *path);
int free_sets(Sets *sets);

int sets_push(Sets *sets, Series *series);
int sets_resize(Sets *sets, ssize_t size);

int popular_series(const Sets *sets);
int print_series(const char *path, const Series *series);
int print_series_from_sets(const char *path, const Sets *sets, ssize_t ind);

#endif  // PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_C_H_
