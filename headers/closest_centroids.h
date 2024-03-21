#ifndef CLOSEST_CENTROIDS_H
#define CLOSEST_CENTROIDS_H


#include "common.h"
#include "params.h"
#include "point.h"
#include "distance.h"


/**
 * @brief Assign the index of the closest centroid to each point
 * @param params Struct with the parameters of the program
 * @return int -1 if an error occurred, 0 if no points have changed their closest centroid, 1 if at least one point has changed its closest centroid
 */
int closest_centroid(params_t* params);

#endif // CLOSEST_CENTROIDS_H
