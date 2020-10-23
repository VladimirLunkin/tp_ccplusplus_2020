#include <stdio.h>
#include "consistently/character_series.h"


int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    const char *path_file = argv[1];

    Sets *sets = create_sets_from_file(path_file);
    if (sets == NULL) {
        return 1;
    }

    ssize_t ind_popular = popular_series(sets);
    if (ind_popular == -1) {
        return 1;
    }

    if (print_series_from_sets(sets, ind_popular) != 0) {
        return 1;
    }

    if (free_sets(sets)) {
        return 1;
    }

    return 0;
}
