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
    printf("HELLO\n");
    int64_t distortion_tot = 0;


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

        distortion_tot += params->squared_distance_func(point_ptr,centroid_ptr); //Add distance from considered point to its centroid to the total distortion
        printf("squa_dis_func(point[%d],centroid[%u]) = %lld\n",i,params->points_list[i].clusterID,params->squared_distance_func(point_ptr,centroid_ptr));
        printf("CURRENT Distortion = %lld\n\n",distortion_tot);
    }
    printf("FINAL Distortion  == %lld\n",distortion_tot);
    return distortion_tot;
}
/*
int main(int argc, char const *argv[]){
    printf("A\n");
    point_t* pts = (point_t*) malloc(sizeof(point_t)*2);
    point_t* cts = (point_t*) malloc(sizeof(point_t)*2);
    params_t* params = (params_t*) malloc(sizeof(params_t));

    int64_t* coordinates_1 = (int64_t*) malloc(sizeof(int64_t)*2);

    coordinates_1[0] = 1;
    coordinates_1[1] = 1;
    point_t p1 = create_point(2,coordinates_1,0);
    pts[0] = p1;

    int64_t* coordinates_2 = (int64_t*) malloc(sizeof(int64_t)*2);
    printf("B\n");

    coordinates_2[0] = 2;
    coordinates_2[1] = 2;
    point_t p2 = create_point(2,coordinates_2,1);
    pts[1] = p2;

    int64_t* coordinates_3 = (int64_t*) malloc(sizeof(int64_t)*2);

    coordinates_3[0] = 0;
    coordinates_3[1] = 0;
    point_t c1 = create_point(2,coordinates_3,0);
    cts[0] = c1;

    int64_t* coordinates_4 = (int64_t*) malloc(sizeof(int64_t)*2);

    coordinates_4[0] = 1;
    coordinates_4[1] = 1;
    point_t c2 = create_point(2,coordinates_4,1);
    cts[1] = c2;
    printf("C\n");
    params->centroids = cts;
    printf("D\n");
    params->points_list = pts;
    printf("E\n");
    params->npoints = 2;
    printf("F\n");
    params->squared_distance_func = squared_euclidean_distance;
    printf("G\n");
    distortion(params);

    return 0;
}
*/





