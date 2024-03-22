#include "../headers/common.h"
#include "../headers/point.h"
#include "../headers/distance.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

int32_t dimension;
point_ptr_t p1, p2;

int init_points_suite(void){
    p1 = (int64_t*) malloc(dimension * sizeof(int64_t));
    p2 = (int64_t*) malloc(dimension * sizeof(int64_t));
    if(p1 == NULL || p2 == NULL) {
        return -1;
    }
    return 0;
}

int clean_points_suite(void){
    free(p1);
    free(p2);
    return 0;
}

/*
* Tests distance between 2 points for every point
*/

void test_manhattan_distance(void) {
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 0;
    p2[1] = 0;
    CU_ASSERT_EQUAL(squared_manhattan_distance(p1, p2, 2), 0);
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 1;
    p2[1] = 1;
    CU_ASSERT_EQUAL(squared_manhattan_distance(p1, p2, 2), 4);
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 1;
    p2[1] = 0;
    CU_ASSERT_EQUAL(squared_manhattan_distance(p1, p2, 2), 1);
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 0;
    p2[1] = 1;
    CU_ASSERT_EQUAL(squared_manhattan_distance(p1, p2, 2), 1);
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 1;
    p2[1] = 2;
    CU_ASSERT_EQUAL(squared_manhattan_distance(p1, p2, 2), 9);
}

void test_euclidean_distance(void) {
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 0;
    p2[1] = 0;
    CU_ASSERT_EQUAL(squared_euclidean_distance(p1, p2, 2), 0);
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 1;
    p2[1] = 1;
    CU_ASSERT_EQUAL(squared_euclidean_distance(p1, p2, 2), 2);
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 1;
    p2[1] = 0;
    CU_ASSERT_EQUAL(squared_euclidean_distance(p1, p2, 2), 1);
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 0;
    p2[1] = 1;
    CU_ASSERT_EQUAL(squared_euclidean_distance(p1, p2, 2), 1);
    p1[0] = 0;
    p1[1] = 0;
    p2[0] = 1;
    p2[1] = 2;
    CU_ASSERT_EQUAL(squared_euclidean_distance(p1, p2, 2), 5);
}

int main() {
    CU_pSuite points_suite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    points_suite = CU_add_suite("points_suite", init_points_suite, clean_points_suite);
    if (NULL == points_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(points_suite, "test_manhattan_distance", test_manhattan_distance)) ||
        (NULL == CU_add_test(points_suite, "test_euclidean_distance", test_euclidean_distance))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int num_failures = CU_get_number_of_failures();

    CU_cleanup_registry();
    return (num_failures == 0) ? 0 : 1;;
}