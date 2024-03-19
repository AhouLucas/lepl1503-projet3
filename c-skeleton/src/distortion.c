#include "../headers/common.h"
#include "../headers/params.h"

/**

Function that calculates the final distortion of all points 
--------------------------
INPUTS:
params : Pointer towards the params of execution of the program, such as the list of points, centroids, the number of points and the distance function
--------------------------
OUTPUT:
Returns: - the total distortion (sum of all distances of each point to their respective centroid)
         - -1 if an error occurred
*/

int64_t distortion(params_t* params){
    int64_t distortion = 0;


    //Check for invalid inputs
    if ((params->points_list == NULL) || (&params->centroids[0] == NULL) || (params->squared_distance_func == NULL)){
        printf("ERROR : Invalid argument");
        return -1;
    }

    for (int i = 0; i < params->npoints ; i++){

        point_t* point_ptr = &(params->points_list[i]); //Create a pointer to the point to be used in the distance function
        if (point_ptr == NULL){
            printf("ERROR : Point is NULL");
            return -1;
        }

        point_t* centroid_ptr = &(params->centroids[params->points_list[i].clusterID]); //Create a pointer to the centroid to be used in the distance function
        if (centroid_ptr == NULL){
            printf("ERROR : This point's centroid is NULL");
            return -1;
        }

        distortion += params->squared_distance_func(point_ptr,centroid_ptr); //Add distance from considered point to its centroid to the total distortion
        printf("squa_dis_func(point[%d],centroid[%u]) = %lld\n",i,params->points_list[i].clusterID,params->squared_distance_func(point_ptr,centroid_ptr));
        printf("CURRENT Distortion = %lld\n\n",distortion);
    }
    printf("FINAL Distortion  == %lld\n",distortion);
    return distortion;
}




