#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "../headers/csv_write.h"
#include <sys/stat.h>

static FILE* temp_file = NULL;
static FILE* verif = NULL ; 
int distortion  ; 

int init_suite() {
    temp_file = fopen("temp.csv", "w+");

    return temp_file == NULL ? -1 : 0;
}

int clean_suite() {
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
    distortion = 12 ;
    
    
     

    point_t initialization_centroids[] = {
        (point_t){ .clusterID = 1, .dimension = 2, .coordinates = p1 },
        (point_t){ .clusterID = 2, .dimension = 2, .coordinates = p2 },
        (point_t){ .clusterID = 3, .dimension = 2, .coordinates = p3 },
    };
    point_t final_centroids[] = {
        (point_t){ .clusterID = 1, .dimension = 2, .coordinates = p1 },
        (point_t){ .clusterID = 2, .dimension = 2, .coordinates = p2 },
        (point_t){ .clusterID = 3, .dimension = 2, .coordinates = p3 },
    };

    point_t points[] = {
        (point_t){ .clusterID = 1, .dimension = 2, .coordinates = p1 },
        (point_t){ .clusterID = 2, .dimension = 2, .coordinates = p2 },
        (point_t){ .clusterID = 3, .dimension = 2, .coordinates = p3 },
        (point_t){ .clusterID = 3, .dimension = 2, .coordinates = p1 },
        (point_t){ .clusterID = 3, .dimension = 2, .coordinates = p2 },
    };
    init_suite() ; 
    params_t params = {
        .centroids = initialization_centroids,
        .points_list = points,
        .npoints = 5,
        .quiet = false,
        .k = 3,
        .output_stream = temp_file,
    };
    write_header_csv(&params) ; 
    write_row_head_csv(&params , final_centroids) ; 
    write_row_tail_csv(&params , distortion);
    
    fflush(temp_file);
    clean_suite() ; 

    

}
void test_check_file_content_and_size() {
    FILE* temp_file_read = fopen("temp.csv", "r");
    if (temp_file_read == NULL) {
        CU_FAIL("Could not open temp.csv for reading");
        return;
    }

    //  taille du fichier pour allouer mémoire 
    struct stat st;
    if (stat("temp.csv", &st) != 0) {
        fclose(temp_file_read);
        CU_FAIL("Could not get file size of temp.csv");
        return;
    }
    off_t file_size = st.st_size;

    char expected_content[] = "initialization centroids,distortion,centroids,clusters\n\"[(1, 1), (2, 2), (3, 4)]\",12,\"[(1, 1), (2, 2), (3, 4)]\",\"[[(1, 1)], [(2, 2)], [(3, 4), (1, 1), (2, 2)]]\"\n";
    char actual_content[file_size + 1];

    size_t bytes_read = fread(actual_content, 1, file_size, temp_file_read);
    if (bytes_read != file_size) {
        fclose(temp_file_read);
        CU_FAIL("Reading temp.csv failed");
        return;
    }
    fclose(temp_file_read);

    actual_content[file_size] = '\0'; 

    // printf("Expected content:\n%s\n", expected_content);
    // printf("Actual content:\n%s\n", actual_content);
    // printf("Bytes read by fread: %zu\n", bytes_read);

    CU_ASSERT_STRING_EQUAL(actual_content, expected_content);
}

int main() {
    CU_pSuite pSuite = NULL;
    
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    pSuite = CU_add_suite("Suite 1", init_suite, clean_suite);

    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_add_test(pSuite, "test_write_row", test_write_row);
    CU_add_test(pSuite, "test_check_file_content_and_size", test_check_file_content_and_size);

    CU_basic_set_mode(CU_BRM_VERBOSE); // Définir le mode de sortie pour obtenir un résumé détaillé des tests

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}