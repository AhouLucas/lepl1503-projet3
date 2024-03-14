
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../headers/resultat_to_csv.h"
#include "../headers/common.h"
#include "../headers/point.h"


point_t *initial_centroids;
int distortion = 10;
point_t *final_centroids ; 
point_t **clusters;
int num_clusters ;

void Correct_execution() {
    const char *filename = "output.csv"; // Nom du fichier de sortie

    point_t initial_centroids[] = {
        {.dimension = 2, .coordinates = (int64_t[]){2, 2}},
        {.dimension = 2, .coordinates = (int64_t[]){3, 4}},
        {.dimension = 2, .coordinates = (int64_t[]){5, 6}}
    };
    int distortion = 10;
    point_t final_centroids[] = {
        {.dimension = 2, .coordinates = (int64_t[]){7, 8}},
        {.dimension = 2, .coordinates = (int64_t[]){9, 10}},
        {.dimension = 2, .coordinates = (int64_t[]){11, 12}}
    };
    point_t **clusters;
    int num_clusters = 3;

    // Allocation et initialisation de clusters (à des fins de démonstration)
    clusters = malloc(num_clusters * sizeof(point_t *));
    for (int i = 0; i < num_clusters; i++) {
        clusters[i] = malloc(num_clusters * sizeof(point_t));
        for (int j = 0; j < num_clusters; j++) {
            clusters[i][j].dimension = 2;
            clusters[i][j].coordinates = (int64_t[]){i * num_clusters + j, i * num_clusters + j + 1};
        }
    }
    
    // Exécuter la fonction à tester
    int result = write_to_csv("test_output.csv", initial_centroids, distortion, final_centroids, &clusters, num_clusters);

    // Vérifier le résultat
    CU_ASSERT_EQUAL(result, 0);

    for (int i = 0; i < num_clusters; i++) {
        free(clusters[i]);
    }
    
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