#include "../headers/common.h"
#include "../headers/distance.h"
#include "../headers/point.h"

/*
Function that calculates the final distortion of all points 
--------------------------
INPUTS:
squared_distance_func_t : Function that calculates the distance between 2 points (represented as pointers)
final_points : List of the final position of the points
final_centroids : List of the final position of the centroids
num_points : Number of points to consider 
--------------------------
OUTPUT:
Returns: - the total distortion (sum of all distances of each point to their respective centroid)
         - -1 if an error occurred
*/

int64_t distortion(squared_distance_func_t squared_distance_function, point_t* final_points, point_t* final_centroids, int num_points){
    int64_t distortion = 0;

    //Check for invalid inputs
    if ((final_points == NULL) || (final_centroids == NULL) || (squared_distance_function == NULL)){
        printf("ERROR : Invalid argument");
        return -1;
    }

    for (int i = 0; i < num_points ; i++){

        if (&(final_points[i]) == NULL){
            printf("ERROR : Point is NULL");
            return -1;
        }
        if (&(final_centroids[final_points[i].clusterID]) == NULL){
            printf("ERROR : This point's centroid is NULL");
            return -1;
        }

        point_t* point_ptr = &(final_points[i]); //Create a pointer to the point to be used in the distance function
        point_t* centroid_ptr = &(final_centroids[final_points[i].clusterID]); // Create a pointer to the centroid to be used in the distance function

        distortion += squared_distance_function(point_ptr,centroid_ptr); //Add distance from considered point to its centroid to the total distortion
    }
    printf("Distortion %ld",distortion);
    return distortion;
}