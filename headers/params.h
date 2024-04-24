#ifndef PARAMS_H
#define PARAMS_H

#include <stdbool.h>
#include "common.h"
#include "point.h"
#include "distance.h"


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
    point_list_t points_list;
    point_list_t centroids;
    uint32_t *cluster_ids;
    uint32_t *cluster_sizes;
    point_list_t cluster_means;
} __attribute__ ((aligned(16))) params_t;

#endif