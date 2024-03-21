#include "../headers/distance.h"
#include "../headers/common.h"

uint64_t squared_manhattan_distance(const point_ptr_t p1, const point_ptr_t p2, uint64_t dim) {
    uint64_t sum = 0;
    int64_t diff = 0;
    for (uint32_t i = 0; i < dim; i++) {
        diff =  p1[i] - p2[i];
        if(diff < 0) {
            sum -= diff;
            continue;
        }
        sum += diff;
    }
    
    return sum*sum;
}


uint64_t squared_euclidean_distance(const point_ptr_t p1, const point_ptr_t p2, uint32_t dim) {
    uint64_t sum = 0;
    int64_t diff = 0;
    for (uint32_t i = 0; i < dim; i++) {
        diff = p1[i] - p2[i];
        sum += diff*diff;
    }
    
    return sum;
}

