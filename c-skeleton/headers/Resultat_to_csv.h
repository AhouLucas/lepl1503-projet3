#ifndef RESULTAT_TO_CSV
#define RESULTAT_TO_CSV

#include "common.h"

typedef struct {
    int64_t x;
    int64_t y;
} tuple_t;

/**
 * @brief Return a csv file in correct format 
 * 
 * @param initial_centroids Array of initial centroids of type point_t
 * 
 * @param distortion Distortion of the final array of centroids
 * 
 * @param final_centroids Array of final centroids of type point_t 
 * 
 * @param clusters Array of Array of the differents cluster 
 * 
 * @return int -1 if an error occurred, 0 if no file could be created, 1 if the file have been correctly intialised 
 */

int write_to_csv(const char *filename, tuple_t *initial_centroids, int distortion, tuple_t *final_centroids, tuple_t ***clusters, int num_clusters);

#endif 