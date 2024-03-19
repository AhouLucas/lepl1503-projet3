#include "../headers/common.h"
#include "../headers/point.h"
#include "../headers/distance.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>


int32_t dimension;
point_t p1, p2;


int init_points_suite(void){
    dimension = 2;
    p1.dimension = dimension;
    p1.coordinates = (int64_t*) malloc(dimension * sizeof(int64_t));
    p2.dimension = dimension;
    p2.coordinates = (int64_t*) malloc(dimension * sizeof(int64_t));
    if(p1.coordinates == NULL || p2.coordinates == NULL) {
        return -1;
    }
    return 0;
}

int clean_points_suite(void){
    free(p1.coordinates);
    free(p2.coordinates);
    return 0;
}

/*
* Tests distance between 2 points for every point
*/

void test_manhattan_distance(void) {
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 0;
    p2.coordinates[1] = 0;
    CU_ASSERT_EQUAL(squared_manhattan_distance(&p1, &p2), 0);
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 1;
    p2.coordinates[1] = 1;
    CU_ASSERT_EQUAL(squared_manhattan_distance(&p1, &p2), 4);
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 1;
    p2.coordinates[1] = 0;
    CU_ASSERT_EQUAL(squared_manhattan_distance(&p1, &p2), 1);
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 0;
    p2.coordinates[1] = 1;
    CU_ASSERT_EQUAL(squared_manhattan_distance(&p1, &p2), 1);
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 1;
    p2.coordinates[1] = 2;
    CU_ASSERT_EQUAL(squared_manhattan_distance(&p1, &p2), 9);
}

void test_euclidean_distance(void) {
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 0;
    p2.coordinates[1] = 0;
    CU_ASSERT_EQUAL(squared_euclidean_distance(&p1, &p2), 0);
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 1;
    p2.coordinates[1] = 1;
    CU_ASSERT_EQUAL(squared_euclidean_distance(&p1, &p2), 2);
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 1;
    p2.coordinates[1] = 0;
    CU_ASSERT_EQUAL(squared_euclidean_distance(&p1, &p2), 1);
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 0;
    p2.coordinates[1] = 1;
    CU_ASSERT_EQUAL(squared_euclidean_distance(&p1, &p2), 1);
    p1.coordinates[0] = 0;
    p1.coordinates[1] = 0;
    p2.coordinates[0] = 1;
    p2.coordinates[1] = 2;
    CU_ASSERT_EQUAL(squared_euclidean_distance(&p1, &p2), 5);
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
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}