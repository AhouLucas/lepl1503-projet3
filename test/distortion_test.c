#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/common.h"
#include "../headers/point.h"
#include "../headers/params.h"
#include "../headers/distortion.h"
#include "../headers/distance.h"

params_t *params;
point_list_t centroids;
point_list_t points;
uint32_t *cluster_ids;
int32_t dimension;
uint32_t k;
uint64_t num_points;

int init_distortion_suite(void) {
    dimension = 2;
    k = 3;
    num_points = 5;
    params = (params_t*) malloc(sizeof(params_t));
    centroids = (point_list_t) malloc(k * dimension * sizeof(int64_t));
    points = (point_list_t) malloc(num_points * dimension * sizeof(int64_t));
    cluster_ids = (uint32_t*) malloc(num_points * sizeof(uint32_t));

    if(params == NULL || centroids == NULL || points == NULL || cluster_ids == NULL) {
        return 1;
    }

    // Initialize the centroids
    centroids[0] = 0; centroids[1] = 0; // centroid 0
    centroids[2] = 1; centroids[3] = 1; // centroid 1
    centroids[4] = -1; centroids[5] = 1; // centroid 2

    // Initialize the points
    points[0] = 0; points[1] = 0; // point 0
    points[2] = 2; points[3] = 2; // point 1
    points[4] = -2; points[5] = 2; // point 2
    points[6] = 1; points[7] = 1; // point 3
    points[8] = -1; points[9] = 2; // point 4

    // Initialize the cluster_ids
    cluster_ids[0] = 0;
    cluster_ids[1] = 1;
    cluster_ids[2] = 2;
    cluster_ids[3] = 1;
    cluster_ids[4] = 2;

    params->k = k;
    params->npoints = num_points;
    params->dimension = dimension;
    params->squared_distance_func = squared_euclidean_distance;
    params->points_list = points;
    params->cluster_ids = cluster_ids;
    params->centroids = centroids;

    return 0;
}

int clean_distortion_suite(void) {
    free(params);
    free(centroids);
    free(points);
    free(cluster_ids);
    return 0;
}


void test_distortion(void) {
    CU_ASSERT_EQUAL(distortion(params), 5);
}

void test_distortion_null_centroids(void) {
    params->centroids = NULL;
    CU_ASSERT_EQUAL(distortion(params), -1);
}

void test_distortion_null_points(void) {
    params->centroids = centroids;
    params->points_list = NULL;
    CU_ASSERT_EQUAL(distortion(params), -1);
}

void test_distortion_null_distance_func(void) {
    params->points_list = points;
    params->squared_distance_func = NULL;
    CU_ASSERT_EQUAL(distortion(params), -1);
}

void test_distortion_null_cluster_ids(void) {
    params->squared_distance_func = squared_euclidean_distance;
    params->cluster_ids = NULL;
    CU_ASSERT_EQUAL(distortion(params), -1);
}


int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("distortion_suite", init_distortion_suite, clean_distortion_suite);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(pSuite, "test_distortion", test_distortion) == NULL ||
        CU_add_test(pSuite, "test_distortion_null_centroids", test_distortion_null_centroids) == NULL ||
        CU_add_test(pSuite, "test_distortion_null_points", test_distortion_null_points) == NULL ||
        CU_add_test(pSuite, "test_distortion_null_distance_func", test_distortion_null_distance_func) == NULL ||
        CU_add_test(pSuite, "test_distortion_null_cluster_ids", test_distortion_null_cluster_ids) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int num_failures = CU_get_number_of_failures();

    CU_cleanup_registry();
    return (num_failures == 0) ? 0 : 1;;
}