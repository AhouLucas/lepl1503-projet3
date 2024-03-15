#include "../headers/common.h"
#include "../headers/point.h"

point_t create_point(uint32_t dimension, int64_t* coordinates, uint32_t clusterID) {
    point_t p;
    p.dimension = dimension;
    p.clusterID = clusterID;
    int64_t* coord = (int64_t*) malloc(sizeof(int64_t) * dimension);
    for(uint32_t j = 0 ; j < dimension ; j++) {
        coord[j] = coordinates[j];
    }
    p.coordinates = coord;
    return p;
}

void free_points(point_t* points, uint32_t n) {
    for(uint32_t j = 0 ; j < n ; j++) {
        free(points[j].coordinates);
    }
    free(points);
}

int copy_point(point_t* dest, const point_t* src) {
    uint32_t d = src->dimension;
    dest->dimension = d;
    dest->clusterID = src->clusterID;
    int64_t* coord = (int64_t*) malloc(sizeof(int64_t) * d);
    if(coord == NULL) {
        return 1;
    }
    for(uint32_t j = 0 ; j < d ; j++) {
        coord[j] = src->coordinates[j];
    }
    dest->coordinates = coord;
    return 0;
}

void print_point(point_t* p, uint32_t detailed) {
    if(detailed == 1) {
        printf("{d:%d,cID:%d}",p->dimension,p->clusterID);
    }
    printf("(");
    for(uint32_t i = 0 ; i < p->dimension ; i++) {
        printf("%ld", (p->coordinates)[i]);
        if(i < p->dimension -1) printf(",");
    }
    printf(")\n");
}

int compare_point(point_t* p1, point_t* p2) {
    int assert_dim = p1->dimension == p2->dimension;
    int assert_cID = p1->clusterID == p2->clusterID;
    if(assert_dim == 0 || assert_cID == 0) return 0;
    for(uint32_t i = 0 ; i < p1->dimension ; i++) {
        int assert_coord = p1->coordinates[i] == p2->coordinates[i];
        if(assert_coord == 0) return 0;
    }
    return 1;
}