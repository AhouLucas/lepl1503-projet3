#include "../headers/distance.h"

uint64_t squared_manhattan_distance(const point_t *p1, const point_t *p2) {
    uint64_t sum = 0;
    int64_t diff = 0;
    for (uint32_t i = 0; i < p1->dimension; i++) {
        diff = p1->coordinates[i] - p2->coordinates[i];
        if(diff < 0) {
            sum -= diff;
            continue;
        }
        sum += diff;
    }
    
    return sum*sum;
}


uint64_t squared_euclidean_distance(const point_t *p1, const point_t *p2) {
    uint64_t sum = 0;
    int64_t diff = 0;
    for (uint32_t i = 0; i < p1->dimension; i++) {
        diff = p1->coordinates[i] - p2->coordinates[i];
        sum += diff*diff;
    }
    
    return sum;
}

