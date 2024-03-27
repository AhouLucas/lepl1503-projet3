#include "../headers/common.h"
#include "../headers/params.h"
#include "../headers/point.h"
#include "../headers/distance.h"


uint64_t distortion(params_t* params){
    uint64_t distortion = 0;

    if(params->points_list == NULL || params->centroids == NULL || params->cluster_ids == NULL){
        return -1;
    }

    for (uint64_t i = 0; i < params->npoints; i++){  // For every point
        switch (params->squared_distance_func) {
        case SQUARED_DISTANCE_MANHATTAN/* constant-expression */:
            distortion += squared_manhattan_distance(get_point(params->points_list, i, params->dimension) , get_point(params->centroids, params->cluster_ids[i], params->dimension), params->dimension);   // Computes the squared distance to its centroid;
            break;
        case SQUARED_DISTANCE_EUCLIDEAN:
            distortion += squared_euclidean_distance(get_point(params->points_list, i, params->dimension) , get_point(params->centroids, params->cluster_ids[i], params->dimension), params->dimension);   // Computes the squared distance to its centroid;
            break;
        default:
            break;
        }
    }

    return distortion;
}