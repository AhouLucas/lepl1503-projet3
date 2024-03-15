#ifndef PARAMS_H
#define PARAMS_H

#include <stdbool.h>
#include "common.h"
#include "point.h"

typedef struct {
    FILE *input_stream;
    FILE *output_stream;
    uint32_t n_threads;
    uint32_t k;
    uint32_t n_first_initialization_points;
    bool quiet;
    squared_distance_func_t squared_distance_func;

    uint32_t dimension;
    uint64_t npoints;
    point_t* points_list;
} params_t;

#endif