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

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

// Inspired by https://www.geeksforgeeks.org/binomial-coefficient-dp-9/
uint64_t nbr_combinations(uint32_t k, uint32_t n) {
    int C[k + 1];
    memset(C, 0, sizeof(C));
 
    C[0] = 1;
 
    for (int i = 1; i <= n; i++) {
        for (int j = min(i, k); j > 0; j--) {
            C[j] = C[j] + C[j - 1];
        }
    }

    return C[k];
}

static uint32_t generate_indices(uint64_t* indices) {   // updates k indices for the next combination
    uint32_t i, j;
    for (i=k-1 ; i >= 0 && indices[i] == i+n-k ; i--);  // find most right indice that can be incremented
    if (i < 0) return 0;                                // if none, i = -1 so all combinations made
    indices[i]++;
    for (j=i+1 ; j < k ; j++) {                         // reset indices to the right of i
        indices[j] = indices[j-1] + 1;
    }
    return 1;                                           // successfully found next combination
}

int32_t generate_all_combinations_iter(params_t* parameters, point_list_t mem) {
    dim = parameters->dimension;                        // set up global variables
    k = parameters->k;
    n = parameters->n_first_initialization_points;
    pool = parameters->points_list;
    combinations_index = 0;
    uint64_t n_comb = nbr_combinations(k, n);           // computes number of combinations for size
    uint64_t* indices = (uint64_t*) malloc(k*sizeof(uint64_t));
    for(uint32_t i = 0 ; i < k ; i++) {                 // generates first combination
        indices[i] = i;
        memcpy(get_point(mem, dim, i), get_point(pool, dim, i), sizeof(int64_t)*dim);
    }
    combinations_index++;

    while(combinations_index < n_comb && generate_indices(indices) == 1) { //uses generate_indices to find indices of points forming the combination
        for(uint32_t i = 0 ; i < k ; i++) {
            memcpy(get_point(mem, dim, (combinations_index*k +i)), get_point(pool, dim, indices[i]), sizeof(int64_t)*dim);
        }
        combinations_index++;
    }
    free(indices);
    return 0;
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