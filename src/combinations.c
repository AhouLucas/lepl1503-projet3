#include "../headers/common.h"
#include "../headers/params.h"
#include "../headers/point.h"
#include "../headers/combinations.h"

static uint32_t dim;
static uint32_t k;
static uint32_t n;
static point_list_t pool;
static uint64_t combinations_index;
static point_list_t memory;

uint64_t fact_aux(uint64_t n, uint64_t r) {
    if(n == 1) return r;
    else return fact_aux(n-1, r*n);
}

uint64_t fact(uint64_t n) {
    if(n == 0 || n == 1) return 1;
    return fact_aux(n-1, n);
}

uint64_t nbr_combinations(uint32_t k, uint32_t n) {
    return fact(n)/(fact(n-k)*fact(k));
}

static void generate_combination(point_list_t current_comb, uint32_t recursion, uint32_t j) {
    if(recursion == k) {
        for(uint32_t i = 0 ; i < k ; i++) {
            memcpy(get_point(memory, dim, (combinations_index*k +i)), get_point(current_comb, dim, i), sizeof(int64_t)*dim);
        }
        combinations_index++;
        return;
    }
    if(j>=n) {
        return;
    }
    memcpy(get_point(current_comb, dim, recursion), get_point(pool, dim, j), sizeof(int64_t)*dim);
    generate_combination(current_comb, recursion+1, j+1);
    generate_combination(current_comb, recursion, j+1);
}
    

int32_t generate_all_combinations(params_t* parameters, point_list_t mem) {
    dim = parameters->dimension;
    k = parameters->k;
    n = parameters->n_first_initialization_points;
    pool = parameters->points_list;
    memory = mem;
    combinations_index = 0;
    
    point_list_t buffer = (point_list_t) malloc(sizeof(int64_t) * k * dim);

    if (buffer == NULL) {
        printf("Couldn't malloc in generate_all_combinations");
        exit(EXIT_FAILURE);
    }

    generate_combination(buffer, 0, 0);
    free(buffer);
    return 0;
}