
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../headers/resultat_to_csv.h"
#include "../headers/common.h"


tuple_t* initial_centroids ; 
int distortion = 10;
tuple_t* final_centroids ; 
tuple_t **clusters; 
int num_clusters ;

void Correct_execution() {
    tuple_t initial_centroids[] = {{1, 2}, {3, 4}};
    int distortion = 5;
    tuple_t final_centroids[] = {{6, 7}, {8, 9}};
    tuple_t **clusters = malloc(2 * sizeof(tuple_t *));
    clusters[0] = malloc(2 * sizeof(tuple_t));
    clusters[1] = malloc(2 * sizeof(tuple_t));
    clusters[0][0] = (tuple_t){10, 11};
    clusters[0][1] = (tuple_t){12, 13};
    clusters[1][0] = (tuple_t){14, 15};
    clusters[1][1] = (tuple_t){16, 17};
    int num_clusters = 2;
    
    // Exécuter la fonction à tester
    int result = write_to_csv("test_output.csv", initial_centroids, distortion, final_centroids, &clusters, num_clusters);

    // Vérifier le résultat
    CU_ASSERT_EQUAL(result, 0);

    // Nettoyer les ressources allouées
    free(clusters[0]);
    free(clusters[1]);
    free(clusters);
}

int main() {
    CU_initialize_registry();


    CU_pSuite suite = CU_add_suite("Suite de tests pour write_to_csv", NULL, NULL);
    CU_add_test(suite, "Test de write_to_csv", Correct_execution);


    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}