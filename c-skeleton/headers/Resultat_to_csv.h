#ifndef RESULTAT_TO_CSV
#define RESULTAT_TO_CSV

#include "common.h"
#include "point.h"
#include "params.h"



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

int write_to_csv(params_t* input , point_t *initial_centroids, int distortion, point_t *final_centroids);

#endif 