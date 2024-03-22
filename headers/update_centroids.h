#ifndef UPDATE_CENTROIDS_H
#define UPDATE_CENTROIDS_H

#include "common.h"
#include "params.h"
#include "point.h"

/**
 * @brief Compute the new centroids from the the current vectors
 * @param params Structure that contains commons variables
 * @return int -1 if an error occurred, 0 otherwise
 */
int update_centroids(params_t* params);

#endif // UPDATE_CENTROIDS_H