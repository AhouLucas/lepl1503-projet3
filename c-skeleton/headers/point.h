#ifndef POINT_H
#define POINT_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int32_t dimension;
    int64_t* coordinates;
    uint32_t clusterID;
} point_t;

#endif //POINT_H
