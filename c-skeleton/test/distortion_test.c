#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/common.h"
#include "../headers/point.h"
#include "../headers/params.h"
#include "../headers/distortion.h"
#include "../headers/distance.h"

params_t *params;
point_t *centroids;
point_t *points;

point_t p1, p2, p3, p4, p5;
point_t c1, c2, c3;

int init_distortion_suite(void) {
    params = (params_t*) malloc(sizeof(params_t));
    centroids = (point_t*) malloc(3 * sizeof(point_t));
    points = (point_t*) malloc(5 * sizeof(point_t));

    if(params == NULL || centroids == NULL || points == NULL) {
        return 1;
    }

    params->k = 3;
    params->npoints = 5;
    params->squared_distance_func = squared_euclidean_distance;

    p1 = (point_t) {2, (int64_t[]) {1, 1}, 1};
    p2 = (point_t) {2, (int64_t[]) {-1, 2}, 2};
    p3 = (point_t) {2, (int64_t[]) {0, 0}, 0};
    p4 = (point_t) {2, (int64_t[]) {0, -1}, 1};
    p5 = (point_t) {2, (int64_t[]) {2, 2}, 1};

    c1 = (point_t) {2, (int64_t[]) {0, 0}, 0};
    c2 = (point_t) {2, (int64_t[]) {1, 1}, 0};
    c3 = (point_t) {2, (int64_t[]) {-1, 1}, 0};

    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;

    centroids[0] = c1;
    centroids[1] = c2;
    centroids[2] = c3;

    params->points_list = points;
    params->centroids = centroids;

    return 0;
}

int clean_distortion_suite(void) {
    free(params);
    free(centroids);
    free(points);
    return 0;
}


void test_distortion(void) {
    CU_ASSERT_EQUAL(distortion(params), 4);
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

void test_distortion_negative_num_points(void) {
    params->points_list = points;
    params->npoints = -1;
    CU_ASSERT_EQUAL(distortion(params), -1);
}

void test_distortion_negative_k(void) {
    params->npoints = 5;
    params->k = -1;
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
        CU_add_test(pSuite, "test_distortion_negative_num_points", test_distortion_negative_num_points) == NULL ||
        CU_add_test(pSuite, "test_distortion_negative_k", test_distortion_negative_k) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}