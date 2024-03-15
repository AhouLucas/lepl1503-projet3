#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../headers/point.h"

point_t p1 = {2, (int64_t[]){1, 1}, 0};
point_t p2;
point_t p3 = {2, (int64_t[]){1, 1}, 0};
point_t p4 = {2, (int64_t[]){1, 2}, 0};

void test_create_point(void) {
    point_t p = create_point(2, (int64_t[]){1, 1}, 0);
    CU_ASSERT_TRUE(compare_point(&p, &p1));
    free(p.coordinates);
}

void test_copy_point(void) {
    int r = copy_point(&p2, &p1);
    CU_ASSERT_FALSE(r);
    CU_ASSERT_TRUE(compare_point(&p1, &p2));
}

void test_print_point(void) {
    print_point(&p1, 1);
    CU_ASSERT_TRUE(1);
}

void test_compare_point(void) {
    CU_ASSERT_TRUE(compare_point(&p1, &p3));
    CU_ASSERT_FALSE(compare_point(&p1, &p4));
}

int teardown(void) {
    free(p2.coordinates);
}

int main(int argc, char* argv[]) {

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("Point utils", NULL, teardown);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((NULL == CU_add_test(pSuite, "Compare", test_compare_point))||
        (NULL == CU_add_test(pSuite, "Copy", test_copy_point))||
        (NULL == CU_add_test(pSuite, "Create", test_create_point))||
        (NULL == CU_add_test(pSuite, "Print", test_print_point))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    CU_cleanup_registry();
    return 0;
}