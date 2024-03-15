#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/common.h"
#include "../headers/distortion.h"
#include "../headers/distance.h"


void init_point_2D(point_t point, uint32_t clusterID, int64_t x, int64_t y, uint32_t dimension){
    point.clusterID = clusterID;

    int64_t* coordinnates_point = (int64_t*) malloc(sizeof(int64_t)*2);
    coordinnates_point[0] = x;
    coordinnates_point[1] = y;

    point.coordinates = coordinnates_point;
    point.dimension = 2;
}

    void init_point_3D(point_t point, uint32_t clusterID, int64_t x, int64_t y, int64_t z, uint32_t dimension){
    point.clusterID = clusterID;

    int64_t* coordinnates_point = (int64_t*) malloc(sizeof(int64_t)*3);
    coordinnates_point[0] = x;
    coordinnates_point[1] = y;
    coordinnates_point[2] = z;

    point.coordinates = coordinnates_point;
    point.dimension = 3;
}

point_t* test_points;
point_t* test_centroids;
int nmb_points = 5;
int nmb_centroids = 3;
int nmb_dimensions = 2;


void init(void){

    test_points = (point_t*) malloc(sizeof(point_t) * nmb_points); // 5 Points to test
    test_centroids = (point_t*) malloc(sizeof(point_t) * nmb_centroids); // 3 Centroids to test

    for (int j = 0; j < nmb_centroids; j++){
        init_point_2D(test_centroids[j],j,j,j,nmb_dimensions);    
    }

    for (int i = 0; i < nmb_points ; i++){
        if (i < 2){
            init_point_2D(test_points[i],0,i,1+i,nmb_dimensions);  //Assign centroid to each point arbitrarely (Point 0,1 have centroid 0)
        }
        if (i < 4){
            init_point_2D(test_points[i],1,i,1+i,nmb_dimensions);  //Assign centroid to each point arbitrarely (Point 2,3 have centroid 1)
        }
        else {
            init_point_2D(test_points[i],2,i,1+i,nmb_dimensions);  //Assign centroid to each point arbitrarely (Point 4 have centroid 2)
        }
}
}


void test_distortion_simple(void) {
    CU_ASSERT_EQUAL(distortion(squared_euclidean_distance, test_points, test_centroids, nmb_points), 1);
    //CU_ASSERT_EQUAL(distortion(1), 1);
    //CU_ASSERT_EQUAL(distortion(5), 120);
    //CU_ASSERT_EQUAL(distortion(15), 1307674368000);
}


int main(int argc, char const *argv[])
{
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    CU_pSuite pSuite = CU_add_suite("Distortion",init,NULL);
    if (pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite,"Test Distortion",test_distortion_simple)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    CU_cleanup_registry();
    return 0;
}






