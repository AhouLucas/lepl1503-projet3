#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/csv_write.h"

void test_write_csv() {
    int64_t p1[] = {1, 1};
    int64_t p2[] = {2, 2};
    int64_t p3[] = {3, 4};
    
    point_t initialization_centroids[] = {
        (point_t){ .clusterID = -1, .dimension = 2, .coordinates = p1 },
        (point_t){ .clusterID = -1, .dimension = 2, .coordinates = p2 },
        (point_t){ .clusterID = -1, .dimension = 2, .coordinates = p3 },
    };

    point_t points[] = {
        (point_t){ .clusterID = 1, .dimension = 2, .coordinates = p1 },
        (point_t){ .clusterID = 2, .dimension = 2, .coordinates = p2 },
        (point_t){ .clusterID = 3, .dimension = 2, .coordinates = p3 },
        (point_t){ .clusterID = 3, .dimension = 2, .coordinates = p1 },
        (point_t){ .clusterID = 3, .dimension = 2, .coordinates = p2 },
    };

    params_t params = {
        .centroids = initialization_centroids,
        .points_list = points,
        .npoints = 5,
        .quiet = false,
        .k = 3,
    };

    write_row_csv(stdout, initialization_centroids, 15, &params);
}

int main() {
    test_write_csv();
}