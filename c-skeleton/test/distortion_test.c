#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/common.h"
#include "../headers/params.h"
#include "../headers/distortion.h"
#include "../headers/distance.h"

point_t* test_points;
point_t* test_centroids;
params_t* params;
int nmb_points = 5;
int nmb_centroids = 3;
int nmb_dimensions = 2;

int init(void){
    params = (params_t*) malloc(sizeof(params_t));

    test_points = (point_t*) malloc(sizeof(point_t) * nmb_points); // 5 Points to test
    test_centroids = (point_t*) malloc(sizeof(point_t) * nmb_centroids); // 3 Centroids to test

    if ((test_points == NULL) || (test_centroids == NULL)){
        return -1;
    }

    for (int i = 0; i < 5; i++){ // Generate 5 points
        int64_t* coordinates_i = (int64_t*) malloc(sizeof(int64_t)*2);

        if (coordinates_i == NULL){
            printf("ERROR: Malloc failed");
            return -1;
        }

        coordinates_i[0] = i;
        coordinates_i[1] = i + 1;

        point_t point_i;
        if (i<2){
        point_t point_i = create_point(nmb_dimensions,coordinates_i,0);
        }
        if (i<4){
        point_t point_i = create_point(nmb_dimensions,coordinates_i,1);
        }
        else {
        point_t point_i = create_point(nmb_dimensions,coordinates_i,2);
        }
        test_points[i] = point_i;
    }


    for (int i = 0; i < 3; i++){ // Generate 3 centroids
        int64_t* coordinates_i = (int64_t*) malloc(sizeof(int64_t)*2);

        if (coordinates_i == NULL){
            printf("ERROR: Malloc failed");
            return -1;
        }

        coordinates_i[0] = i;
        coordinates_i[1] = i;

        point_t point_i = create_point(nmb_dimensions,coordinates_i,0);
        test_centroids[i] = point_i;
    }
    printf("A\n");
    params->centroids = test_centroids;
    params->points_list = test_points;
    squared_distance_func_t* func = (squared_distance_func_t*) malloc(sizeof(squared_distance_func_t));
    printf("B\n");
    params->squared_distance_func = squared_euclidean_distance;
    printf("C\n");
    params->dimension = nmb_dimensions;
    params->npoints = nmb_points;

    // -------------------------------
    // TO DO :
    // INITIALIZE POINTS (#5)
    // INITIALIZE CENTROIDS (#3)
    // CALCULATE THEORETICAL VALUE OF DISTORTION FOR GIVEN VALUES
    // -------------------------------
}
/*
int free(void){

    // -------------------------------
    // TO DO :
    // FREE ALLOCATED MEMORY FOR TESTS
    // -------------------------------

    return 0;
}
*/

int64_t theoretical_distortion_simple = 37; // ##### CHANGE WITH CALCULATED VALUE ######

void test_distortion_simple(void) {
    printf("D\n");
    CU_ASSERT_EQUAL(distortion(params), theoretical_distortion_simple);
    printf("E\n");
}


int main(int argc, char const *argv[])
{
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    CU_pSuite pSuite = CU_add_suite("Distortion",init,NULL);
    if (pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite,"Test Distortion Simple",test_distortion_simple)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    CU_cleanup_registry();
    return 0;
}






