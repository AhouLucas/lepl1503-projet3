#include "../headers/common.h"
#include "../headers/params.h"
#include "../headers/point.h"
#include "../headers/combinations.h"

uint64_t fact(uint64_t n) {
    if(n == 0 || n == 1) return 1;
    uint64_t fact_aux(uint64_t n, uint64_t r) {
        if(n == 1) return r;
        else return fact_aux(n-1, r*n);
    }
    return fact_aux(n-1, n);
}

uint64_t nbr_combinations(uint32_t k, uint32_t n) {
    return fact(n)/(fact(n-k)*fact(k));
}

int32_t generate_all_combinations(params_t* parameters, point_t* memory) {
    uint32_t k = parameters->k;
    uint32_t n = parameters->n_first_initialization_points;
    point_t* pool = parameters->points_list;
    if(k > n) return -1;
    point_t* pre = (point_t*) malloc(sizeof(point_t) * k);
    uint64_t index = 0;

    void generate_combination(point_t* pre, uint32_t recursion, uint32_t j) {
        if(recursion == k) {
            for(int i = 0 ; i < k ; i++) {
                copy_point(memory+(index*k +i), pre+i);
            }
            index++;
            return;
        }
        if(j>=n) {
            return;
        }
        if(j != 0) {
            free((pre+recursion)->coordinates);
        }
        copy_point(pre+recursion, pool+j);
        generate_combination(pre, recursion+1, j+1);
        generate_combination(pre, recursion, j+1);
    }
    
    generate_combination(pre, 0, 0);
    free_points(pre, k);
    return 0;
}