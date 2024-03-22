#include "../headers/common.h"
#include "../headers/params.h"
#include "../headers/point.h"
#include "../headers/distance.h"
#include "../headers/closest_centroids.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

params_t *params;
point_list_t centroids;
point_list_t points;
uint32_t *cluster_ids;
int32_t dimension;
int k;
int num_points;
squared_distance_func_t squared_distance_function;

int init_wrong_param_suite(void) {
    k = 3;
    num_points = 5;
    centroids = (point_list_t) malloc(k * dimension * sizeof(int64_t));
    points = (point_list_t) malloc(num_points * dimension * sizeof(int64_t));
    cluster_ids = (uint32_t*) malloc(num_points * sizeof(uint32_t));
    params = (params_t*) malloc(sizeof(params_t));
    squared_distance_function = squared_euclidean_distance;

    if(centroids == NULL || points == NULL || params == NULL) {
        return 1;
    }

    params->k = k;
    params->npoints = num_points;
    params->squared_distance_func = squared_distance_function;
    params->points_list = points;
    params->cluster_ids = cluster_ids;
    params->centroids = centroids;
    params->dimension = 2;
    return 0;
}

int clean_wrong_param_suite(void) {
    free(centroids);
    free(points);
    free(cluster_ids);
    free(params);
    return 0;
}

/*
* Tests for wrong parameters suite
*/

void test_centroids_null(void) {
    params->centroids = NULL;
    CU_ASSERT_EQUAL(closest_centroid(params), -1);
}

void test_points_null(void) {
    params->centroids = centroids;
    params->points_list = NULL;
    CU_ASSERT_EQUAL(closest_centroid(params), -1);
}

void test_squared_distance_function_null(void) {
    params->cluster_ids = cluster_ids;
    params->squared_distance_func = NULL;
    CU_ASSERT_EQUAL(closest_centroid(params), -1);
}



int init_closest_centroids_suite(void) {
    dimension = 2;
    k = 3;
    num_points = 5;
    centroids = (point_list_t) malloc(k * dimension * sizeof(int64_t));
    points = (point_list_t) malloc(num_points * dimension * sizeof(int64_t));
    cluster_ids = (uint32_t*) malloc(num_points * sizeof(uint32_t));
    params = (params_t*) malloc(sizeof(params_t));
    squared_distance_function = squared_euclidean_distance;
    if(centroids == NULL || points == NULL || params == NULL) {
        return 1;
    }

    // Initialize centroids
    centroids[0] = 0; centroids[1] = 0; // Centroid 0
    centroids[2] = 1; centroids[3] = 1; // Centroid 1
    centroids[4] = -1; centroids[5] = 1; // Centroid 2

    // Initialize points
    points[0] = 0; points[1] = 0; // Point 0 : Centroid 0
    points[2] = 2; points[3] = 1; // Point 1 : Centroid 1
    points[4] = -1; points[5] = 2; // Point 2 : Centroid 2
    points[6] = 0; points[7] = 1; // Point 3 : Centroid 0
    points[8] = 0; points[9] = -2; // Point 4 : Centroid 0

    // Initialize cluster_ids
    cluster_ids[0] = 10;
    cluster_ids[1] = 10;
    cluster_ids[2] = 10;
    cluster_ids[3] = 10;
    cluster_ids[4] = 10;

    params->k = k;
    params->npoints = num_points;
    params->squared_distance_func = squared_distance_function;
    params->points_list = points;
    params->centroids = centroids;
    params->cluster_ids = cluster_ids;
    params->dimension = dimension;
    params->n_threads = 1;
    params->n_first_initialization_points = 1;
    params->quiet = false;

    return 0;
}

int clean_closest_centroids_suite(void) {
    free(centroids);
    free(points);
    free(cluster_ids);
    free(params);
    return 0;
}

/*
* Tests for closest_centroids suite
*/

void test_closest_centroids(void) {
    CU_ASSERT_EQUAL(closest_centroid(params), 1);
    CU_ASSERT_EQUAL(params->cluster_ids[0], 0);
    CU_ASSERT_EQUAL(params->cluster_ids[1], 1);
    CU_ASSERT_EQUAL(params->cluster_ids[2], 2);
    CU_ASSERT_EQUAL(params->cluster_ids[3], 0);
    CU_ASSERT_EQUAL(params->cluster_ids[4], 0);
}

void test_closest_centroids_no_change(void) {
    CU_ASSERT_EQUAL(closest_centroid(params), 0);
    CU_ASSERT_EQUAL(params->cluster_ids[0], 0);
    CU_ASSERT_EQUAL(params->cluster_ids[1], 1);
    CU_ASSERT_EQUAL(params->cluster_ids[2], 2);
    CU_ASSERT_EQUAL(params->cluster_ids[3], 0);
    CU_ASSERT_EQUAL(params->cluster_ids[4], 0);
}

int main() {
    CU_pSuite wrong_param_suite = NULL;
    CU_pSuite closest_centroids_suite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    wrong_param_suite = CU_add_suite("Wrong parameters suite", init_wrong_param_suite, clean_wrong_param_suite);
    if (NULL == wrong_param_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    closest_centroids_suite = CU_add_suite("Closest centroids suite", init_closest_centroids_suite, clean_closest_centroids_suite);
    if (NULL == closest_centroids_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(wrong_param_suite, "Test centroids NULL", test_centroids_null)) ||
        (NULL == CU_add_test(wrong_param_suite, "Test points NULL", test_points_null)) ||
        (NULL == CU_add_test(wrong_param_suite, "Test squared_distance_function NULL", test_squared_distance_function_null)) ||
        (NULL == CU_add_test(closest_centroids_suite, "Test closest centroids", test_closest_centroids)) ||
        (NULL == CU_add_test(closest_centroids_suite, "Test closest centroids no change", test_closest_centroids_no_change))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int num_failures = CU_get_number_of_failures();

    CU_cleanup_registry();
    return (num_failures == 0) ? 0 : 1;;
}