#ifndef UPDATE_CENTROIDS_H
#define UPDATE_CENTROIDS_H

#include "common.h"
#include "params.h"
#include "point.h"

/**
 * @brief Updates the centroids based on the current assignment of data points.
 * 
 * This function first checks if the centroids, points list, cluster IDs, and cluster sizes in the params structure are not NULL.
 * If any of them are NULL, the function returns -1.
 * 
 * Then, it resets the cluster sizes and centroids to 0.
 * 
 * It then iterates over each point in the dataset, and for each point, it adds the point's coordinates to the corresponding centroid's coordinates
 * and increments the size of the cluster that the point is assigned to.
 * 
 * Finally, it calculates the mean of each coordinate of each centroid by dividing the sum of the coordinates by the size of the cluster,
 * and updates the centroid's coordinates with these means.
 * 
 * @param params The parameters containing the dataset, centroids, and assignments.
 * @return int Returns 0 if successful, and -1 if any of the centroids, points list, cluster IDs, or cluster sizes are NULL.
 */
int update_centroids(params_t* params);

#endif // UPDATE_CENTROIDS_H