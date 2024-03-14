#ifndef POINT_H
#define POINT_H

#include "common.h"

typedef struct {
    uint32_t dimension;
    int64_t* coordinates;
    uint32_t clusterID;
} point_t;

#endif //POINT_H
