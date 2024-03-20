#include "../headers/common.h"
#include "../headers/params.h"
#include "../headers/point.h"
#include "../headers/distance.h"


uint64_t distortion(params_t* params){
    uint64_t distortion = 0;

    for (uint64_t i = 0; i < params->npoints; i++){  // For every point
        distortion += params->squared_distance_func(params->points_list+i, params->centroids + params->points_list[i].clusterID);   // Computes the squared distance to its centroid
    }

    return distortion;
}