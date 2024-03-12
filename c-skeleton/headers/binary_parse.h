#ifndef BINARY_PARSE_H
#define BINARY_PARSE_H

#include <stdint.h>
#include "point.h"


typedef struct {
    uint32_t dimension;
    uint64_t npoints;
    point_t* points_list;
} params_t;

params_t* binary_parse(FILE*);

void free_params_struct(params_t*);

#endif