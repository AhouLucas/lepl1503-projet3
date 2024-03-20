#ifndef CSV_WRITE
#define CSV_WRITE

#include "common.h"
#include "point.h"
#include "params.h"


void write_header_csv(params_t *params);
void write_row_head_csv(params_t *params, point_t *initialization_centroids);
void write_row_tail_csv(params_t *params, uint64_t distortion);


#endif // CSV_WRITE