#include "../headers/distance.h"

int64_t squared_manhattan_distance(const point_t *p1, const point_t *p2) {
    int32_t n = p1->dimension;
    if(n != p2->dimension) {
        printf("Dimension error : Points must have the same dimension");
        return -1;
    }

    int64_t sum = 0;
    int64_t diff = 0;
    for (int i = 0; i < n; i++) {
        diff = p1->coordinates[i] - p2->coordinates[i];
        if(diff < 0) {
            sum -= diff;
            continue;
        }
        sum += diff;
    }
    
    return sum*sum;
}


int64_t squared_euclidean_distance(const point_t *p1, const point_t *p2) {
    int32_t n = p1->dimension;
    if(n != p2->dimension) {
        printf("Dimension error : Points must have the same dimension");
        return -1;
    }

    int64_t sum = 0;
    int64_t diff = 0;
    for (int i = 0; i < n; i++) {
        diff = p1->coordinates[i] - p2->coordinates[i];
        sum += diff*diff;
    }
    
    return sum;
}

