#include "../headers/common.h"
#include "../headers/combinations.h"

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

static point_t* init_pool;
static point_t* buffer_combinations;
static uint32_t dimension = 2;

int init(void) {
    init_pool = (point_t*) malloc(sizeof(point_t) * 5);
    buffer_combinations = (point_t*) malloc(sizeof(point_t) * 30);

    if(init_pool == NULL || buffer_combinations == NULL) return 1;

    for(uint32_t i = 0 ; i < 5 ; i++) {
        point_t* p = init_pool+i;
        p->dimension = dimension;
        p->clusterID = 0;           // clusterID is irrelevant
        int64_t* coord = (int64_t*) malloc(sizeof(int64_t) * dimension);
        if(coord == NULL) {
            printf("Error while copying point");
        }
        for(uint32_t j = 0 ; j < dimension ; j++) {
            coord[j] = i+1;         // coordinates like (x,x) for easier verification
        }
        p->coordinates = coord;
    }

    int32_t error = generate_all_combinations(init_pool, buffer_combinations, 3, 5);
    if(error == -1) return 1;

    return 0;
}

int teardown(void) {
    free(init_pool);

    for(int i = 0 ; i < 30 ; i++) {
        free(buffer_combinations[i].coordinates);
    }
    free(buffer_combinations);
}

void print_point2(point_t* p) {
    printf("(");
    for(uint32_t i = 0 ; i < p->dimension ; i++) {
        printf("%ld", (p->coordinates)[i]);
        if(i < p->dimension -1) printf(",");
    }
    printf(")\n");
}

void compare_points(point_t* p1, point_t* p2) {
    CU_ASSERT_TRUE(compare_point(p1, p2));
}

void test_combinations(void) {
    compare_points(buffer_combinations+0, init_pool+0);
    compare_points(buffer_combinations+1, init_pool+1);
    compare_points(buffer_combinations+2, init_pool+2);

    compare_points(buffer_combinations+3, init_pool+0);
    compare_points(buffer_combinations+4, init_pool+1);
    compare_points(buffer_combinations+5, init_pool+3);

    compare_points(buffer_combinations+6, init_pool+0);
    compare_points(buffer_combinations+7, init_pool+1);
    compare_points(buffer_combinations+8, init_pool+4);

    compare_points(buffer_combinations+9, init_pool+0);
    compare_points(buffer_combinations+10, init_pool+2);
    compare_points(buffer_combinations+11, init_pool+3);

    compare_points(buffer_combinations+12, init_pool+0);
    compare_points(buffer_combinations+13, init_pool+2);
    compare_points(buffer_combinations+14, init_pool+4);

    compare_points(buffer_combinations+15, init_pool+0);
    compare_points(buffer_combinations+16, init_pool+3);
    compare_points(buffer_combinations+17, init_pool+4);

    compare_points(buffer_combinations+18, init_pool+1);
    compare_points(buffer_combinations+19, init_pool+2);
    compare_points(buffer_combinations+20, init_pool+3);

    compare_points(buffer_combinations+21, init_pool+1);
    compare_points(buffer_combinations+22, init_pool+2);
    compare_points(buffer_combinations+23, init_pool+4);

    compare_points(buffer_combinations+24, init_pool+1);
    compare_points(buffer_combinations+25, init_pool+3);
    compare_points(buffer_combinations+26, init_pool+4);

    compare_points(buffer_combinations+27, init_pool+2);
    compare_points(buffer_combinations+28, init_pool+3);
    compare_points(buffer_combinations+29, init_pool+4);
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

    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    CU_cleanup_registry();
    return 0;
}