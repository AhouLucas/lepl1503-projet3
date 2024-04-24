#ifndef KMEANS_H
#define KMEANS_H

#include "common.h"
#include "point.h"
#include "distance.h"
#include "params.h"

typedef struct {
    params_t* params;
    uint32_t* partial_sum;
    size_t start_idx;
    size_t end_idx;
    pthread_barrier_t* barrier;
    bool *cancel;
} thread_data_t;

/**
 * @brief Executes the k-means clustering algorithm.
 * 
 * This function runs the k-means clustering algorithm on the dataset specified in the params structure.
 * It starts by assigning each point to the closest centroid, then updates the centroids based on the current assignments.
 * This process is repeated until the assignments no longer change.
 * 
 * @param params The parameters containing the dataset, centroids, and assignments.
 */
void kmeans(params_t *params);

#endif // KMEANS_H