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
        point_t point = parameters.points_list[i];
        printf("(%d,%d)",point.coordinates[0],point.coordinates[1]);
    }
    CU_ASSERT_TRUE(1);
}

int init(void) {
    FILE* file = fopen("../../python/exemple.bin", "r");
    if(file == NULL) {
        return 1;
    }
    uint32_t output = binary_parse(file, &parameters);
    fclose(file);
    printf("%d",output);
    return 0;
}

int teardown(void) {
    free_params_struct(&parameters);
    return 0;
}

int main(int argc, char* argv[]) {
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
    CU_basic_show_failures(CU_get_failure_list());
    CU_cleanup_registry();
    return 0;
}