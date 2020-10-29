#ifndef PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_P_H_
#define PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_P_H_

#define INIT_NUMBER_SERIES 10
#define NUMBER_OF_PROCESSES 2

#include <stdlib.h>
#include "consistently/character_series_c.h"

//Sets *create_sets();
//Sets *create_sets_from_file(const char *path);
//int free_sets(Sets *sets);

//int sets_push(Sets *sets, Series *series);
//int sets_resize(Sets *sets, ssize_t size);

int multi_popular_series(const Sets *sets);
//int print_series(const char *path, const Series *series);
//int print_series_from_sets(const char *path, const Sets *sets, ssize_t ind);

#endif  // PROJECT_INCLUDE_CONSISTENTLY_CHARACTER_SERIES_P_H_
