#include "../headers/common.h"
#include "../headers/closest_centroids.h"
#include "../headers/point.h"
#include "../headers/distance.h"
#include "../headers/params.h"

int closest_centroid(params_t* params){
    int k = params->k;
    int num_points = params->npoints;
    point_list_t points = params->points_list;
    point_list_t centroids = params->centroids;
    squared_distance_func_t squared_distance_function = params->squared_distance_func;
    // Check for parameter and return -1 if there is a wrong parameter
    if(centroids == NULL || points == NULL || k < 0 || num_points < 0 || squared_distance_function == NULL) {
        return -1;
    }

    int changed = 0;
    
    for(int i = 0; i < num_points; i++) {   // For each point
        point_ptr_t p = get_point(points, params->dimension, i);//&points[i];
        uint32_t oldClusterID = params->cluster_id[i];  // Remember the old centroid to know if it has changed
        uint64_t minDistance = UINT64_MAX;

        for(int centroidIndex = 0; centroidIndex < k; centroidIndex++) {   // For each centroid
            point_ptr_t c = get_point(points, params->dimension, centroidIndex);
            uint64_t dist = squared_distance_function(p, c, params->dimension); 

            if(dist < minDistance) {    // Update point clusterID if it's closer 
                params->cluster_id[i] = (uint32_t)centroidIndex;
                minDistance = dist;
            }
        }
        if(params->cluster_id[i] != oldClusterID) {
            changed = 1;
        }
    }

    return changed;
}