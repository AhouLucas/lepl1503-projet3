#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include "common.h"
#include "point.h"
#include "params.h"

/**
 * @brief Compute the factorial of n. (Tail-recursive)
 * 
 * @param n Positive integer
 * @return uint64_t the factorial of n, -1 if n < 0. (0! = 1! = 1)
 */
uint64_t fact(uint64_t n);

/**
 * @brief Compute the number of k-selection in a n-set.
 * 
 * @param k Number of elements picked
 * @param n Number of elements in the set
 * @return uint64_t the number of combinations.
 */
uint64_t nbr_combinations(uint32_t k, uint32_t n);

/**
 * @brief Generates all combinations of k-selection in a n-set. Should replicate the behaviour of itertools.combinations (Python)
 * Takes in a pointer that must have been malloc with size=nbr_combinations(k, n).
 * 
 * @param parameters Structure containing the set of points used to form combinations, k and the n.
 * @param memory Array used to buffer the combinations
 * @return int32_t 0 for success, -1 for failure or illegal arguments
 */
int32_t generate_all_combinations(params_t* parameters, point_list_t memory);

#endif