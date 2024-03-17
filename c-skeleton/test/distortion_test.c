#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/common.h"
#include "../headers/distortion.h"
#include "../headers/distance.h"

point_t* test_points;
point_t* test_centroids;
int nmb_points = 5;
int nmb_centroids = 3;
int nmb_dimensions = 2;

int init(void){

    test_points = (point_t*) malloc(sizeof(point_t) * nmb_points); // 5 Points to test
    test_centroids = (point_t*) malloc(sizeof(point_t) * nmb_centroids); // 3 Centroids to test

    if ((test_points == NULL) || (test_centroids == NULL)){
        return -1;
    }
    // -------------------------------
    // TO DO :
    // INITIALIZE POINTS (#5)
    // INITIALIZE CENTROIDS (#3)
    // CALCULATE THEORETICAL VALUE OF DISTORTION FOR GIVEN VALUES
    // -------------------------------
}

int free(void){

    // -------------------------------
    // TO DO :
    // FREE ALLOCATED MEMORY FOR TESTS
    // -------------------------------

    return 0;
}

int64_t theoretical_distortion_simple = 0; // ##### CHANGE WITH CALCULATED VALUE ######

void test_distortion_simple(void) {
    CU_ASSERT_EQUAL(distortion(squared_euclidean_distance, test_points, test_centroids, nmb_points), theoretical_distortion_simple);
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






