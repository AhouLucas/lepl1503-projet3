#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/common.h"
#include "../headers/point.h"
#include "../headers/combinations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void test_factorial_simple(void) {
    CU_ASSERT_EQUAL(fact(0), 1);
    CU_ASSERT_EQUAL(fact(1), 1);
    CU_ASSERT_EQUAL(fact(5), 120);
    CU_ASSERT_EQUAL(fact(15), 1307674368000);
}

void test_binomial_numbers(void) {
    CU_ASSERT_EQUAL(nbr_combinations(10, 10), 1);
    CU_ASSERT_EQUAL(nbr_combinations(3, 5), 10);
    CU_ASSERT_EQUAL(nbr_combinations(5, 10), 252);
}

static params_t* parameters;
static point_list_t init_pool;
static point_list_t buffer_combinations;
static uint32_t dimension = 2;

int init(void) {
    parameters = (params_t*) malloc(sizeof(params_t));
    parameters->k = 3;
    parameters->n_first_initialization_points = 5;
    init_pool = (point_list_t) malloc(sizeof(int64_t) * 5 * dimension);
    buffer_combinations = (point_list_t) malloc(sizeof(int64_t) * 30 * dimension);

    if(init_pool == NULL || buffer_combinations == NULL) return 1;

    for(uint32_t i = 0 ; i < 5 ; i++) {
        point_ptr_t p = get_point(init_pool, dimension, i);
        for(uint32_t j = 0 ; j < dimension ; j++) {
            p[j] = i+1;         // coordinates like (x,x) for easier verification
        }
    }
    parameters->points_list = init_pool;
    parameters->dimension = dimension;

    int32_t error = generate_all_combinations(parameters, buffer_combinations);
    if(error != 0) return 1;

    return 0;
}

int teardown(void) {
    free(init_pool);
    free(parameters);
    free(buffer_combinations);
    return 0;
}

void compare_points(point_ptr_t p1, point_ptr_t p2) {
    int r = 1;
    for(uint32_t i = 0 ; i < dimension ; i++) {
        if(p1[i] != p2[i]) {
            r = 0;
            break;
        }
    }
    CU_ASSERT_TRUE(r);
}

void test_combinations(void) {
    compare_points(get_point(buffer_combinations, dimension, 0), get_point(init_pool, dimension, 0));
    compare_points(get_point(buffer_combinations, dimension, 1), get_point(init_pool, dimension, 1));
    compare_points(get_point(buffer_combinations, dimension, 2), get_point(init_pool, dimension, 2));

    compare_points(get_point(buffer_combinations, dimension, 3), get_point(init_pool, dimension, 0));
    compare_points(get_point(buffer_combinations, dimension, 4), get_point(init_pool, dimension, 1));
    compare_points(get_point(buffer_combinations, dimension, 5), get_point(init_pool, dimension, 3));

    compare_points(get_point(buffer_combinations, dimension, 6), get_point(init_pool, dimension, 0));
    compare_points(get_point(buffer_combinations, dimension, 7), get_point(init_pool, dimension, 1));
    compare_points(get_point(buffer_combinations, dimension, 8), get_point(init_pool, dimension, 4));

    compare_points(get_point(buffer_combinations, dimension, 9), get_point(init_pool, dimension, 0));
    compare_points(get_point(buffer_combinations, dimension, 10), get_point(init_pool, dimension, 2));
    compare_points(get_point(buffer_combinations, dimension, 11), get_point(init_pool, dimension, 3));

    compare_points(get_point(buffer_combinations, dimension, 12), get_point(init_pool, dimension, 0));
    compare_points(get_point(buffer_combinations, dimension, 13), get_point(init_pool, dimension, 2));
    compare_points(get_point(buffer_combinations, dimension, 14), get_point(init_pool, dimension, 4));

    compare_points(get_point(buffer_combinations, dimension, 15), get_point(init_pool, dimension, 0));
    compare_points(get_point(buffer_combinations, dimension, 16), get_point(init_pool, dimension, 3));
    compare_points(get_point(buffer_combinations, dimension, 17), get_point(init_pool, dimension, 4));

    compare_points(get_point(buffer_combinations, dimension, 18), get_point(init_pool, dimension, 1));
    compare_points(get_point(buffer_combinations, dimension, 19), get_point(init_pool, dimension, 2));
    compare_points(get_point(buffer_combinations, dimension, 20), get_point(init_pool, dimension, 3));

    compare_points(get_point(buffer_combinations, dimension, 21), get_point(init_pool, dimension, 1));
    compare_points(get_point(buffer_combinations, dimension, 22), get_point(init_pool, dimension, 2));
    compare_points(get_point(buffer_combinations, dimension, 23), get_point(init_pool, dimension, 4));

    compare_points(get_point(buffer_combinations, dimension, 24), get_point(init_pool, dimension, 1));
    compare_points(get_point(buffer_combinations, dimension, 25), get_point(init_pool, dimension, 3));
    compare_points(get_point(buffer_combinations, dimension, 26), get_point(init_pool, dimension, 4));

    compare_points(get_point(buffer_combinations, dimension, 27), get_point(init_pool, dimension, 2));
    compare_points(get_point(buffer_combinations, dimension, 28), get_point(init_pool, dimension, 3));
    compare_points(get_point(buffer_combinations, dimension, 29), get_point(init_pool, dimension, 4));
}

int main(int argc, char* argv[]) {

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    CU_pSuite pSuite1 = NULL;

    pSuite1 = CU_add_suite("Factorial", NULL, NULL);
    if (NULL == pSuite1) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((NULL == CU_add_test(pSuite1, "Test basic factorial results", test_factorial_simple))||
        (NULL == CU_add_test(pSuite1, "Test simple binomial numbers", test_binomial_numbers))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_pSuite pSuite2 = NULL;

    pSuite2 = CU_add_suite("Combinations", init, teardown);
    if (NULL == pSuite2) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((NULL == CU_add_test(pSuite2, "Test combinations", test_combinations))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int num_failures = CU_get_number_of_failures();

    CU_cleanup_registry();
    return (num_failures == 0) ? 0 : 1;;
}