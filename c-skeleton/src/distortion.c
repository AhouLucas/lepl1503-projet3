#include "../headers/common.h"
#include "../headers/distance.h"
#include "../headers/point.h"

/**

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
    if ((final_points == NULL) || (&final_centroids[0] == NULL) || (squared_distance_function == NULL)){
        printf("ERROR : Invalid argument");
        return -1;
    }

    for (int i = 0; i < num_points ; i++){

        point_t* point_ptr = &(final_points[i]); //Create a pointer to the point to be used in the distance function
        if (point_ptr == NULL){
            printf("ERROR : Point is NULL");
            return -1;
        }

        point_t* centroid_ptr = &(final_centroids[final_points[i].clusterID]); //Create a pointer to the centroid to be used in the distance function
        if (centroid_ptr == NULL){
            printf("ERROR : This point's centroid is NULL");
            return -1;
        }

        distortion += squared_distance_function(point_ptr,centroid_ptr); //Add distance from considered point to its centroid to the total distortion
        printf("squa_dis_func(point[%d],centroid[%u]) = %lld\n",i,final_points[i].clusterID,squared_distance_function(point_ptr,centroid_ptr));
        printf("CURRENT Distortion = %lld\n\n",distortion);
    }
    printf("FINAL Distortion  == %lld\n",distortion);
    return distortion;
}




