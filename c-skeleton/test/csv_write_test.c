#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "../headers/csv_write.h"

static FILE* temp_file = NULL;

void init_suite() {
    temp_file = fopen("temp.txt", "w+");

    return temp_file == NULL ? -1 : 0;
}

void clean_suite() {
    if (fclose(temp_file) == 0) {
        return -1;
    } else {
        temp_file = NULL;
        return 0;
    }
}

void test_write_row() {
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

    write_row_csv(temp_file, initialization_centroids, 15, &params);


}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    pSuite = CU_add_suite("Suite 1", init_suite, clean_suite);

    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    test_write_csv();
}