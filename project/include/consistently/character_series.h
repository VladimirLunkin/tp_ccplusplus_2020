#ifndef PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_H_
#define PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_H_

#define INIT_NUMBER_SERIES 10


struct  Series;
typedef struct Series Series;

struct Sets;
typedef struct Sets Sets;

Sets *create_sets();
Sets *create_sets_from_file(const char *path);
int free_sets(Sets *sets);

int sets_push(Sets *sets, Series *series);
int sets_resize(Sets *sets, ssize_t size);

ssize_t popular_series(const Sets *sets);
int print_series(const Series *series);
int print_series_from_sets(const Sets *sets, ssize_t ind);

#endif  // PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_H_
