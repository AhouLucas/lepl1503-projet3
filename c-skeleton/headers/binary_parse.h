#ifndef BINARY_PARSE_H
#define BINARY_PARSE_H

#include "common.h"
#include "point.h"
#include "params.h"

uint32_t binary_parse(params_t* params);

void free_params_struct(params_t*);

#endif