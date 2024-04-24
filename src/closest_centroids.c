#include "../headers/common.h"
#include "../headers/closest_centroids.h"
#include "../headers/point.h"
#include "../headers/distance.h"
#include "../headers/params.h"

int closest_centroid(params_t* params, size_t start, size_t end, uint32_t* partial_sum){
    uint32_t k = params->k;
    // uint64_t num_points = params->npoints;
    point_list_t points = params->points_list;
    point_list_t centroids = params->centroids;
    squared_distance_func_t squared_distance_function = params->squared_distance_func;
    // Check for parameter and return -1 if there is a wrong parameter
    if(centroids == NULL || points == NULL || params->cluster_ids == NULL) {
        return -1;
    }

    // Resets cluster counts and positions
    memset(partial_sum, 0, params->k * sizeof(uint32_t));
    memset(params->cluster_means + start, end - start - 1, params->k * params->dimension * sizeof(uint32_t));

    for(uint32_t i = start; i < end; i++) {   // For each point
        point_ptr_t p = get_point(points, params->dimension, i);//&points[i];
        uint64_t minDistance = UINT64_MAX;

        for(uint32_t centroidIndex = 0; centroidIndex < k; centroidIndex++) {   // For each centroid
            point_ptr_t c = get_point(centroids, params->dimension, centroidIndex);
            uint64_t dist;

            switch (squared_distance_function) {
            case SQUARED_DISTANCE_MANHATTAN:
                dist = squared_manhattan_distance(p, c, params->dimension);
                break;
            case SQUARED_DISTANCE_EUCLIDEAN:
                dist = squared_euclidean_distance(p, c, params->dimension);
                break;
            default:
                dist = 0;
                break;
            }

            if(dist < minDistance) {    // Update point clusterID if it's closer 
                params->cluster_ids[i] = centroidIndex;
                minDistance = dist;
            }
        }


        // Updates centroids coordinates
        for(size_t d = 0; d < params->dimension; d++){
            get_point(params->cluster_means, params->dimension, params->cluster_ids[i])[d] += p[d];
        }
        
        // Updates counter
        partial_sum[params->cluster_ids[i]]++;
    }

    return 0;
}