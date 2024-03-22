#include "../headers/common.h"
#include "../headers/binary_parse.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

static params_t parameters;

void test_assert_dimension(void) {
    CU_ASSERT_EQUAL(parameters.dimension ,2);
}

void test_assert_npoints(void) {
    CU_ASSERT_EQUAL(parameters.npoints, 7);
}

void test_assert_points_equals(void) {
    for (size_t i = 0; i < 7; i++) {
        // point_ptr_t point = get_point(parameters.points_list, parameters.dimension, i);
    }
    CU_ASSERT_TRUE(1);
}

int init(void) {
    FILE* file = fopen("scripts/exemple.bin", "r");
    if(file == NULL) {
        return 1;
    }

    parameters.input_stream = file;

    uint32_t output = binary_parse(&parameters);
    fclose(file);
    return output;
}

int teardown(void) {
    free_params_struct(&parameters);
    return 0;
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }


    pSuite = CU_add_suite("Ma suite", init, teardown);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    if( (NULL == CU_add_test(pSuite, "Test assert dim", test_assert_dimension)) ||
        (NULL == CU_add_test(pSuite, "Test assert npoints", test_assert_npoints)) ||
        (NULL == CU_add_test(pSuite, "Test assert points equals", test_assert_points_equals))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_basic_run_tests();

    unsigned int num_failures = CU_get_number_of_failures();

    CU_cleanup_registry();
    return (num_failures == 0) ? 0 : 1;;
}