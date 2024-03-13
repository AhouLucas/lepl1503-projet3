#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../headers/common.h"
#include "../headers/update_centroids.h"

point_t* centroids;
point_t* points;
int32_t dimension;
int k;
int num_points;

point_t c1, c2, c3;
point_t p1, p2, p3, p4, p5, p6;

int wrong(void) {
    k = 3;
    num_points = 6;
    dimension = 2;
    centroids = (point_t*) malloc(k * sizeof(point_t));
    points = (point_t*) malloc(num_points * sizeof(point_t));
    if(centroids == NULL || points == NULL) {
        return -1;
    }
}

void test_wrong_input(void){
    CU_ASSERT_EQUAL(update_centroids(NULL, points, k, num_points), -1);
    CU_ASSERT_EQUAL(update_centroids(centroids, NULL, k, num_points), -1);
    CU_ASSERT_EQUAL(update_centroids(centroids, points, -1, num_points), -1);
    CU_ASSERT_EQUAL(update_centroids(centroids, points, k, -1), -1);
    CU_ASSERT_EQUAL(update_centroids(centroids, points, k+1, num_points), -1);
    CU_ASSERT_EQUAL(update_centroids(centroids, points, k, num_points+1), -1);
}

int clean(void) {
    free(centroids);
    free(points);
    return 0;
}

int right(void){
    k = 3;
    num_points = 6;
    dimension = 2;
    centroids = (point_t*) malloc(k * sizeof(point_t));
    points = (point_t*) malloc(num_points * sizeof(point_t));
    if(centroids == NULL || points == NULL) {
        return -1;
    }
    point_t c1 = {dimension, (int64_t[]){0, -1}, 0};
    point_t c2 = {dimension, (int64_t[]){1, 1}, 1};
    point_t c3 = {dimension, (int64_t[]){-1, 1}, 2};

    point_t p1 = {dimension, (int64_t[]){2, -2}, 0};
    point_t p2 = {dimension, (int64_t[]){2, 2}, 1};
    point_t p3 = {dimension, (int64_t[]){-2, 1}, 2};
    point_t p4 = {dimension, (int64_t[]){0, -2}, 0};
    point_t p5 = {dimension, (int64_t[]){2, 0}, 1};
    point_t p6 = {dimension, (int64_t[]){-2, 3}, 2};

    centroids[0] = c1;
    centroids[1] = c2;
    centroids[2] = c3;

    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
    points[5] = p6;
}

void test_classic(void){
    CU_ASSERT_EQUAL(update_centroids(centroids, points, k, num_points), 1);
    CU_ASSERT_EQUAL(centroids[0].coordinates[0], 1);
    CU_ASSERT_EQUAL(centroids[0].coordinates[1], -2);
    CU_ASSERT_EQUAL(centroids[1].coordinates[0], 2);
    CU_ASSERT_EQUAL(centroids[1].coordinates[1], 1);
    CU_ASSERT_EQUAL(centroids[2].coordinates[0], -2);
    CU_ASSERT_EQUAL(centroids[2].coordinates[1], 2);

}

void test_no_change(void){
    CU_ASSERT_EQUAL(update_centroids(centroids, points, k, num_points), 0);
    CU_ASSERT_EQUAL(centroids[0].coordinates[0], (int64_t)1);
    CU_ASSERT_EQUAL(centroids[0].coordinates[1], (int64_t)-2);
    CU_ASSERT_EQUAL(centroids[1].coordinates[0], (int64_t)2);
    CU_ASSERT_EQUAL(centroids[1].coordinates[1], (int64_t)1);
    CU_ASSERT_EQUAL(centroids[2].coordinates[0], (int64_t)-2);
    CU_ASSERT_EQUAL(centroids[2].coordinates[1], (int64_t)2);
}

int main(){
    CU_pSuite wrong_input = NULL;
    CU_pSuite test = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    wrong_input = CU_add_suite("Wrong input", wrong, clean);
    if (NULL == wrong_input) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    test = CU_add_suite("Right input", right, clean);
    if (NULL == test) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(wrong_input, "Test wrong inputs", test_wrong_input)) ||
        (NULL == CU_add_test(test, "Test update centroids", test_classic)) ||
        (NULL == CU_add_test(test, "Test closest centroids no change", test_no_change))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}