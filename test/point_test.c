#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/point.h"

void test_get_point(void) {
    uint32_t dim = 2;
    int64_t points[] = {
            1, 1,
            2, 2,
            3, 3,
    };

    point_ptr_t p1 = get_point(points, dim, 0);
    point_ptr_t p3 = get_point(points, dim, 2);

    CU_ASSERT_EQUAL(p1[0], 1)
    CU_ASSERT_EQUAL(p1[1], 1)
    CU_ASSERT_EQUAL(p3[0], 3)
    CU_ASSERT_EQUAL(p3[1], 3)
}

int main() {
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("Point utils", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((NULL == CU_add_test(pSuite, "Get", test_get_point))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int num_failures = CU_get_number_of_failures();

    CU_cleanup_registry();
    return (num_failures == 0) ? 0 : 1;;
}