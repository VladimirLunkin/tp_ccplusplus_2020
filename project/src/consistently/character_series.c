#include <stdio.h>
#include "consistently/character_series.h"


struct Sets{
    Series *series;
    ssize_t size;
    ssize_t capacity;
};

Sets *create_sets() {
    Sets *sets = (Sets*)malloc(sizeof(Sets));
    if (sets == NULL) {
        return NULL;
    }

    sets->series = (Series*)malloc(INIT_NUMBER_SERIES * sizeof(Series));
    if (sets->series == NULL) {
        free(sets);
        return NULL;
    }

    sets->size = 0;
    sets->capacity = INIT_NUMBER_SERIES;

    return sets;
}
Sets *create_sets_from_file(const char *path) {
    if (path == NULL) {
        return NULL;
    }

    FILE *fptr = fopen(path, "rt");
    if (fptr == NULL) {
        return NULL;
    }

    Sets *sets = create_sets();
    if (sets == NULL) {
        fclose(fptr);
        return NULL;
    }

    Series series = {0, '\n'};
    int current;
    while ((current = fgetc(fptr)) != EOF) {
        if (current == series.symbol) {
            series.length++;
        } else {
            if (series.symbol != '\n' &&
                series.symbol != '\t') {
                if (sets_push(sets, &series) != 0) {
                    break;
                }
            }
            series.symbol = current;
            series.length = 1;
        }
    }

    fclose(fptr);

    return sets;
}
int free_sets(Sets *sets) {
    if (sets == NULL) {
        return 1;
    }

    free(sets->series);
    free(sets);

    return 0;
}

int sets_push(Sets *sets, Series *series) {
    if (sets == NULL || series == NULL) {
        return 1;
    }

    if (sets->size == sets->capacity) {
        if (sets_resize(sets, 2 * sets->capacity) != 0) {
            return 1;
        }
    }

    for (ssize_t i = 0; i < sets->size; ++i) {
        if (sets->series[i].length == series->length) {
            sets->series[i].quantity++;
            return 0;
        }
    }

    sets->series[sets->size].length = series->length;
    sets->series[sets->size].symbol = series->symbol;
    sets->series[sets->size].quantity = 1;
    sets->size++;

    return 0;
}
int sets_resize(Sets *sets, ssize_t size) {
    if (sets == NULL) {
        return 1;
    }

    Series *tmp = (Series*)realloc(sets->series, size * sizeof(Series));
    if (tmp == NULL) {
        return 1;
    }

    sets->series = tmp;
    sets->capacity = size;

    return 0;
}

int popular_series(const Sets *sets) {
    if (sets == NULL) {
        return -1;
    }

    ssize_t ind_popular_series = -1;
    int64_t quantity = 0;
    for (ssize_t i = 0; i < sets->size; ++i) {
        if (quantity < sets->series[i].quantity) {
            quantity = sets->series[i].quantity;
            ind_popular_series = i;
        }
    }

    return ind_popular_series;
}
int print_series(const char *path, const Series *series) {
    if (path == NULL || series == NULL) {
        return 1;
    }

    FILE *fptr = fopen(path, "w");
    if (fptr == NULL) {
        return 1;
    }

    for (int64_t i = 0; i < series->length; ++i) {
        fprintf(fptr, "%c", series->symbol);
    }
    fprintf(fptr, " - %ld\n", series->quantity);

    fclose(fptr);

    return 0;
}
int print_series_from_sets(const char *path, const Sets *sets, ssize_t ind) {
    if (path == NULL || sets == NULL || sets->size <= ind || ind < 0) {
        return 1;
    }

    if (print_series(path, &(sets->series[ind])) != 0) {
        return 1;
    }

    return 0;
}
