#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/point.h"
#include "../headers/params.h"

int update_centroids(params_t* params, size_t start, size_t end) {
    if(params->centroids == NULL || params->points_list == NULL || params->cluster_ids == NULL || params->cluster_sizes == NULL){
        return -1;
    }

    int changed = 0;

    for (size_t i = 0; i < params->k; i++) {
        for (size_t j = 0; j < params->dimension; j++) {
            int64_t mean = get_point(params->cluster_sums, params->dimension, i)[j] / params->cluster_sizes[i];
            changed = get_point(params->centroids, params->dimension, i)[j] != mean;
            get_point(params->centroids, params->dimension, i)[j] = mean;
        }
    }

    return changed;
}
