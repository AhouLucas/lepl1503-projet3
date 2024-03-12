#ifndef PARAMS_H
#define PARAMS_H

#include "common.h"

#include "point.h"

typedef struct {
    uint32_t dimension;
    uint64_t npoints;
    point_t* points_list;
} params_t;

#endif