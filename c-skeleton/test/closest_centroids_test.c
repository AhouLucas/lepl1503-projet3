#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../headers/distance.h"
#include "../headers/closest_centroids.h"


point_t *centroids;
point_t *points;
int32_t dimension;
int k;
int num_points;
squared_distance_func_t squared_distance_function;

point_t p1, p2, p3, p4, p5;
point_t c1, c2, c3;

int init_wrong_param_suite(void) {
    k = 3;
    num_points = 5;
    centroids = (point_t*) malloc(k * sizeof(point_t));
    points = (point_t*) malloc(num_points * sizeof(point_t));
    squared_distance_function = squared_euclidean_distance;
    if(centroids == NULL || points == NULL) {
        return -1;
    }
    return 0;
}

int clean_wrong_param_suite(void) {
    free(centroids);
    free(points);
    return 0;
}

/*
* Tests for wrong parameters suite
*/

void test_centroids_null(void) {
    CU_ASSERT_EQUAL(closest_centroid(NULL, points, k, num_points, squared_distance_function), -1);
}

void test_points_null(void) {
    CU_ASSERT_EQUAL(closest_centroid(centroids, NULL, k, num_points, squared_distance_function), -1);
}

void test_k_negative(void) {
    CU_ASSERT_EQUAL(closest_centroid(centroids, points, -1, num_points, squared_distance_function), -1);
}

void test_num_points_negative(void) {
    CU_ASSERT_EQUAL(closest_centroid(centroids, points, k, -1, squared_distance_function), -1);
}

void test_squared_distance_function_null(void) {
    CU_ASSERT_EQUAL(closest_centroid(centroids, points, k, num_points, NULL), -1);
}

void test_k_not_equal_centroids(void) {
    CU_ASSERT_EQUAL(closest_centroid(centroids, points, k + 69, num_points, squared_distance_function), -1);
}

void test_num_points_not_equal_points(void) {
    CU_ASSERT_EQUAL(closest_centroid(centroids, points, k, num_points + 69, squared_distance_function), -1);
}



int init_closest_centroids_suite(void) {
    dimension = 2;
    k = 3;
    num_points = 5;
    centroids = (point_t*) malloc(k * sizeof(point_t));
    points = (point_t*) malloc(num_points * sizeof(point_t));
    squared_distance_function = squared_euclidean_distance;
    if(centroids == NULL || points == NULL) {
        return -1;
    }

    // Creates 3 centroids
    point_t c1 = {dimension, (int64_t[]){0, 0}, 0};
    point_t c2 = {dimension, (int64_t[]){1, 1}, 0};
    point_t c3 = {dimension, (int64_t[]){-1, 1}, 0};

    // Creates 5 points
    point_t p1 = {dimension, (int64_t[]){0, -1}, 0}; // Belongs to c1
    point_t p2 = {dimension, (int64_t[]){2, 2}, 0}; // Belongs to c2
    point_t p3 = {dimension, (int64_t[]){-2, 1}, 0}; // Belongs to c3
    point_t p4 = {dimension, (int64_t[]){0, -2}, 0}; // Belongs to c1
    point_t p5 = {dimension, (int64_t[]){0, 1}, 0}; // Equidistant to every centroid, so it should belong to c1

    centroids[0] = c1;
    centroids[1] = c2;
    centroids[2] = c3;

    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;

    return 0;
}

int clean_closest_centroids_suite(void) {
    free(centroids);
    free(points);
    return 0;
}

/*
* Tests for closest_centroids suite
*/

void test_closest_centroids(void) {
    CU_ASSERT_EQUAL(closest_centroid(centroids, points, k, num_points, squared_distance_function), 1);
    CU_ASSERT_EQUAL(points[0].clusterID, 0);
    CU_ASSERT_EQUAL(points[1].clusterID, 1);
    CU_ASSERT_EQUAL(points[2].clusterID, 2);
    CU_ASSERT_EQUAL(points[3].clusterID, 0);
    CU_ASSERT_EQUAL(points[4].clusterID, 0);
}

void test_closest_centroids_no_change(void) {
    CU_ASSERT_EQUAL(closest_centroid(centroids, points, k, num_points, squared_distance_function), 0);
    CU_ASSERT_EQUAL(points[0].clusterID, 0);
    CU_ASSERT_EQUAL(points[1].clusterID, 1);
    CU_ASSERT_EQUAL(points[2].clusterID, 2);
    CU_ASSERT_EQUAL(points[3].clusterID, 0);
    CU_ASSERT_EQUAL(points[4].clusterID, 0);
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
        (NULL == CU_add_test(wrong_param_suite, "Test k negative", test_k_negative)) ||
        (NULL == CU_add_test(wrong_param_suite, "Test num_points negative", test_num_points_negative)) ||
        (NULL == CU_add_test(wrong_param_suite, "Test squared_distance_function NULL", test_squared_distance_function_null)) ||
        (NULL == CU_add_test(wrong_param_suite, "Test k not equal centroids", test_k_not_equal_centroids)) ||
        (NULL == CU_add_test(wrong_param_suite, "Test num_points not equal points", test_num_points_not_equal_points)) ||
        (NULL == CU_add_test(closest_centroids_suite, "Test closest centroids", test_closest_centroids)) ||
        (NULL == CU_add_test(closest_centroids_suite, "Test closest centroids no change", test_closest_centroids_no_change))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}