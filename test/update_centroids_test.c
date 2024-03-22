#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/params.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>


params_t* params;
uint32_t k;
uint64_t npoints;
uint32_t dimension;
point_list_t centroids;
point_list_t points;
uint32_t *cluster_ids;
uint32_t *cluster_sizes;

int init_wrong(void) {
    k = 3;
    npoints = 9;
    dimension = 2;
    params = (params_t*) malloc(sizeof(params_t));
    centroids = (point_list_t) malloc(k * dimension * sizeof(int64_t));
    points = (point_list_t) malloc(npoints * dimension * sizeof(int64_t));
    cluster_ids = (uint32_t*) malloc(npoints * sizeof(uint32_t));
    cluster_sizes = (uint32_t*) malloc(k * sizeof(uint32_t));
    if(params==NULL || centroids==NULL || points==NULL || cluster_ids==NULL || cluster_sizes==NULL) {
        return -1;
    }

    params->k = k;
    params->npoints = npoints;
    params->dimension = dimension;
    params->centroids = centroids;
    params->points_list = points;
    params->cluster_ids = cluster_ids;
    params->cluster_sizes = cluster_sizes;

    return 0;
}

void test_wrong_input(void){
    params->centroids = NULL;
    CU_ASSERT_EQUAL(update_centroids(params), -1);
    params->centroids = centroids;
    params->points_list = NULL;
    CU_ASSERT_EQUAL(update_centroids(params), -1);
    params->points_list = points;
    params->cluster_ids = NULL;
    CU_ASSERT_EQUAL(update_centroids(params), -1);
    params->cluster_ids = cluster_ids;
    params->cluster_sizes = NULL;
    CU_ASSERT_EQUAL(update_centroids(params), -1);
    params->cluster_sizes = cluster_sizes;
}

int clean(void) {
    free(params);
    free(centroids);
    free(points);
    free(cluster_ids);
    free(cluster_sizes);
    return 0;
}

int init_right(void){
    k = 3;
    npoints = 9;
    dimension = 2;
    params = (params_t*) malloc(sizeof(params_t));
    centroids = (point_list_t) malloc(k * dimension * sizeof(int64_t));
    points = (point_list_t) malloc(npoints * dimension * sizeof(int64_t));
    cluster_ids = (uint32_t*) malloc(npoints * sizeof(uint32_t));
    cluster_sizes = (uint32_t*) malloc(k * sizeof(uint32_t));

    if(params == NULL || centroids == NULL || points == NULL || cluster_ids == NULL || cluster_sizes == NULL) {
        return 1;
    }

    // Initialize the centroids
    centroids[0] = 0; centroids[1] = 0; // centroid 0
    centroids[2] = 0; centroids[3] = 0; // centroid 1
    centroids[4] = 0; centroids[5] = 0; // centroid 2

    // Initialize the points
    points[0] = 0; points[1] = 0; // point 0
    points[2] = 1; points[3] = 0; // point 1
    points[4] = 2; points[5] = 0; // point 2
    points[6] = 0; points[7] = 1; // point 3
    points[8] = 0; points[9] = 2; // point 4
    points[10] = 0; points[11] = 3; // point 5
    points[12] = 1; points[13] = 1; // point 6
    points[14] = 2; points[15] = 2; // point 7
    points[16] = 3; points[17] = 3; // point 8

    // Initialize the cluster_ids
    cluster_ids[0] = 0;
    cluster_ids[1] = 0;
    cluster_ids[2] = 0;
    cluster_ids[3] = 1;
    cluster_ids[4] = 1;
    cluster_ids[5] = 1;
    cluster_ids[6] = 2;
    cluster_ids[7] = 2;
    cluster_ids[8] = 2;

    params->k = k;
    params->npoints = npoints;
    params->dimension = dimension;
    params->points_list = points;
    params->cluster_ids = cluster_ids;
    params->centroids = centroids;
    params->cluster_sizes = cluster_sizes; 

    return 0;
}


void test_classic(void){
    CU_ASSERT_EQUAL(update_centroids(params), 0);
    CU_ASSERT_EQUAL(get_point(params->centroids, params->dimension, 0)[0], 1);
    CU_ASSERT_EQUAL(get_point(params->centroids, params->dimension, 0)[1], 0);
    CU_ASSERT_EQUAL(get_point(params->centroids, params->dimension, 1)[0], 0);
    CU_ASSERT_EQUAL(get_point(params->centroids, params->dimension, 1)[1], 2);
    CU_ASSERT_EQUAL(get_point(params->centroids, params->dimension, 2)[0], 2);
    CU_ASSERT_EQUAL(get_point(params->centroids, params->dimension, 2)[1], 2);
}


int main(){
    CU_pSuite wrong_input = NULL;
    CU_pSuite test = NULL;

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