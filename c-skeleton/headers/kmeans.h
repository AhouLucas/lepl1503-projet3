#ifndef KMEANS_H
#define KMEANS_H

#include "common.h"
#include "point.h"
#include "distance.h"

void kmeans(point_t *initial_centroids, point_t *points, int k, int num_points, squared_distance_func_t squared_distance_function);

#endif // KMEANS_H