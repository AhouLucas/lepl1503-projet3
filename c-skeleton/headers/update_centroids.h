#ifndef UPDATE_CENTROIDS_H
#define UPDATE_CENTROIDS_H

#include "common.h"

#include "point.h"

/**
 * @brief Compute the new centroids from the the current vectors
 * 
 * @param centroids Array of centroids of type point_t to be updated to become the center of the clusters
 * @param points Array of points of type point_t
 * @param k Number of centroids
 * @param num_points Number of points
 * @return int -1 if an error occurred, 0 if no centroid have changed, 1 if at least one centroid has changed its position
 */
int update_centroids(point_t* centroids, point_t* points, int k, int num_points);

#endif // UPDATE_CENTROIDS_H