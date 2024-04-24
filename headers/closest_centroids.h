#ifndef CLOSEST_CENTROIDS_H
#define CLOSEST_CENTROIDS_H


#include "common.h"
#include "params.h"
#include "point.h"
#include "distance.h"


/**
 * @brief Finds the closest centroid for each point in the dataset.
 * 
 * @param params The parameters containing the dataset and centroids.
 * @return int Returns 0 if successful, and a non-zero error code otherwise.
 */
int closest_centroid(params_t* params, size_t start, size_t end);

#endif // CLOSEST_CENTROIDS_H
