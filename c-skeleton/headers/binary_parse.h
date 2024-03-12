#ifndef BINARY_PARSE_H
#define BINARY_PARSE_H

#include <stdint.h>
#include "point.h"
#include "params.h"

params_t* binary_parse(FILE*);

void free_params_struct(params_t*);

#endif