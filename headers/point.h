#ifndef POINT_H
#define POINT_H

#include "common.h"

typedef int64_t* point_list_t;
typedef int64_t* point_ptr_t;


point_ptr_t get_point(point_list_t list, uint32_t dim, size_t point_index);

#endif //POINT_H
