#ifndef CLOSEST_CENTROIDS_H
#define CLOSEST_CENTROIDS_H


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "point.h"
#include "distance.h"


/**
 * @brief Assign the index of the closest centroid to each point
 * 
 * @param centroids Array of centroids of type point_t
 * @param points Array of points of type point_t to be assigned to the closest centroid
 * @param k Number of centroids
 * @param num_points Number of points
 * @return int -1 if an error occurred, 0 if no points have changed their closest centroid, 1 if at least one point has changed its closest centroid
 */
int closest_centroid(point_t* centroids, point_t *points, int k, int num_points, squared_distance_func_t squared_distance_function);

#endif // CLOSEST_CENTROIDS_H
