#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "../headers/csv_write.h"
#include <sys/stat.h>

static FILE* temp_file = NULL;
int distortion_value  ;

int init_suite() {
    temp_file = fopen("temp.csv", "w+");

    return temp_file == NULL ? -1 : 0;
}

int clean_suite() {
    if (fclose(temp_file) == 0) {
        return 0;
    } else {
        temp_file = NULL;
        return -1;
    }
}



void test_write_row() {
    int64_t points[] = {
            1, 1,
            2, 2,
            3, 3,
    };

    uint32_t cluster_ids[] = {1, 2, 2};
    int64_t centroids[] = {
            1, 1,
            2, 2,
            3, 3,
    };

    distortion_value = 12 ;
    
    init_suite() ;
    params_t params = {
        .centroids = centroids,
        .points_list = points,
        .npoints = 3,
        .quiet = false,
        .k = 3,
        .dimension = 2,
        .cluster_ids = cluster_ids,
        .output_stream = temp_file,
    };
    write_header_csv(&params) ; 
    write_row_head_csv(&params , centroids) ;
    write_row_tail_csv(&params , distortion_value);
    
    fflush(temp_file);
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

    char expected_content[] = "initialization centroids,distortion,centroids,clusters\n\"[(1, 1), (2, 2), (3, 3)]\",12,\"[(1, 1), (2, 2), (3, 3)]\",\"[[], [(1, 1)], [(2, 2), (3, 3)]]\"\n";
    char actual_content[file_size + 1];

    size_t bytes_read = fread(actual_content, 1, file_size, temp_file_read);
    if (bytes_read != file_size) {
        fclose(temp_file_read);
        CU_FAIL("Reading temp.csv failed");
        return;
    }
    fclose(temp_file_read);

    actual_content[file_size] = '\0';

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