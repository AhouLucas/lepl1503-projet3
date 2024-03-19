#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/params.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>


params_t* params;

point_t c1, c2, c3, c4;
point_t p1, p2, p3, p4, p5, p6;

int init_wrong(void) {
    printf("STOP\n");
    params->k = 4;
    printf("STOP\n");
    params->npoints = 6;
    params->dimension = 2;
    params->centroids = (point_t*) malloc(params->k * sizeof(point_t));
    params->points_list = (point_t*) malloc(params->npoints * sizeof(point_t));
    if(params->centroids == NULL || params->points_list == NULL) {
        return -1;
    }
    return 0;
}

void test_wrong_input(void){
    point_t* centroids = params->centroids;
    point_t* points_list =params->points_list;
    params->centroids = NULL;
    CU_ASSERT_EQUAL(update_centroids(params), -1);
    params->centroids = centroids;
    params->points_list=NULL;
    CU_ASSERT_EQUAL(update_centroids(params), -1);
    params->points_list=points_list;
    params->k=-1;
    CU_ASSERT_EQUAL(update_centroids(params), -1);
    params->k=4;
    params->npoints=-1;
    CU_ASSERT_EQUAL(update_centroids(params), -1);
}

int clean(void) {
    free(params->centroids);
    free(params->points_list);
    return 0;
}

int init_right(void){
    params->k = 4;
    params->npoints = 6;
    params->dimension = 2;
    params->centroids = (point_t*) malloc(params->k * sizeof(point_t));
    params->points_list = (point_t*) malloc(params->npoints * sizeof(point_t));
    if(params->centroids == NULL || params->points_list == NULL) {
        return -1;
    }
    return 0;
}


void test_classic(void){
    
    point_t c1 = {params->dimension, (int64_t[]){0, -1}, 0};
    point_t c2 = {params->dimension, (int64_t[]){1, 1}, 1};
    point_t c3 = {params->dimension, (int64_t[]){-1, 1}, 2};
    point_t c4 = {params->dimension, (int64_t[]){-5, -5}, 3}; //empty cluster

    point_t p1 = {params->dimension, (int64_t[]){2, -2}, 0};
    point_t p2 = {params->dimension, (int64_t[]){2, 2}, 1};
    point_t p3 = {params->dimension, (int64_t[]){-2, 1}, 2};
    point_t p4 = {params->dimension, (int64_t[]){0, -2}, 0};
    point_t p5 = {params->dimension, (int64_t[]){2, 0}, 1};
    point_t p6 = {params->dimension, (int64_t[]){-2, 3}, 2};

    params->centroids[0] = c1;
    params->centroids[1] = c2;
    params->centroids[2] = c3;
    params->centroids[3] = c4;

    params->points_list[0] = p1;
    params->points_list[1] = p2;
    params->points_list[2] = p3;
    params->points_list[3] = p4;
    params->points_list[4] = p5;
    params->points_list[5] = p6;
    CU_ASSERT_EQUAL(update_centroids(params), 1);
    CU_ASSERT_EQUAL(params->centroids[0].coordinates[0], 1);
    CU_ASSERT_EQUAL(params->centroids[0].coordinates[1], -2);
    CU_ASSERT_EQUAL(params->centroids[1].coordinates[0], 2);
    CU_ASSERT_EQUAL(params->centroids[1].coordinates[1], 1);
    CU_ASSERT_EQUAL(params->centroids[2].coordinates[0], -2);
    CU_ASSERT_EQUAL(params->centroids[2].coordinates[1], 2);
    CU_ASSERT_EQUAL(params->centroids[3].coordinates[0], -5);
    CU_ASSERT_EQUAL(params->centroids[3].coordinates[1], -5);

    //test if centroids are already in the center
    CU_ASSERT_EQUAL(update_centroids(params), 0);
    CU_ASSERT_EQUAL(params->centroids[0].coordinates[0], 1);
    CU_ASSERT_EQUAL(params->centroids[0].coordinates[1], -2);
    CU_ASSERT_EQUAL(params->centroids[1].coordinates[0], 2);
    CU_ASSERT_EQUAL(params->centroids[1].coordinates[1], 1);
    CU_ASSERT_EQUAL(params->centroids[2].coordinates[0], -2);
    CU_ASSERT_EQUAL(params->centroids[2].coordinates[1], 2);
    CU_ASSERT_EQUAL(params->centroids[3].coordinates[0], -5);
    CU_ASSERT_EQUAL(params->centroids[3].coordinates[1], -5);


}


int main(){
    CU_pSuite wrong_input = NULL;
    CU_pSuite test = NULL;
    CU_pSuite no_change = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    wrong_input = CU_add_suite("Wrong input", init_wrong, clean);
    if (NULL == wrong_input) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    test = CU_add_suite("Right input", init_right, clean);
    if (NULL == test) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(wrong_input, "Test wrong inputs", test_wrong_input)) ||
        (NULL == CU_add_test(test, "Test classic", test_classic))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}