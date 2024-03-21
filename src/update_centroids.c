#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/point.h"
#include "../headers/params.h"

void update_centroids(params_t* params){
    memset(params->cluster_sizes, 0, params->k * sizeof(uint32_t));
    memset(params->centroids, 0, params->k * params->dimension * sizeof(int64_t));

    for (size_t i = 0; i < params->npoints; i++) {
        for (size_t j = 0; j < params->dimension; j++) {
            int64_t coordinate = get_point(params->points_list, params->dimension, i)[j];
            get_point(params->centroids, params->dimension, params->cluster_ids[i])[j] += coordinate;
        }

        params->cluster_sizes[params->cluster_ids[i]]++;
    }

    for (size_t i = 0; i < params->k; i++) {
        for (size_t j = 0; j < params->dimension; j++) {
            uint32_t mean = get_point(params->centroids, params->dimension, i)[j] / params->cluster_sizes[i];
            get_point(params->centroids, params->dimension, i)[j] = mean;
        }
    }
}
