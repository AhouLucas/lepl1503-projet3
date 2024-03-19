#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../headers/resultat_to_csv.h"
#include "../headers/common.h"
#include "../headers/point.h"

point_t *initial_centroids;
int distortion = 10;
point_t *final_centroids;
point_t *clusters;
int num_clusters;

void Correct_execution() {
    const char *filename = "output.csv"; // Nom du fichier de sortie

    

    // Initialisation des centroides initiaux et finaux en tant que tableaux de point_t
    initial_centroids = malloc(2 * sizeof(point_t));
    initial_centroids[0].dimension = 2;
    initial_centroids[0].coordinates = malloc(initial_centroids[0].dimension * sizeof(long));
    initial_centroids[0].coordinates[0] = 1;
    initial_centroids[0].coordinates[1] = 2;

    initial_centroids[1].dimension = 2;
    initial_centroids[1].coordinates = malloc(initial_centroids[1].dimension * sizeof(long));
    initial_centroids[1].coordinates[0] = 3;
    initial_centroids[1].coordinates[1] = 4;

    final_centroids = malloc(2 * sizeof(point_t));
    final_centroids[0].dimension = 2;
    final_centroids[0].coordinates = malloc(final_centroids[0].dimension * sizeof(long));
    final_centroids[0].coordinates[0] = 5;
    final_centroids[0].coordinates[1] = 6;

    final_centroids[1].dimension = 2;
    final_centroids[1].coordinates = malloc(final_centroids[1].dimension * sizeof(long));
    final_centroids[1].coordinates[0] = 7;
    final_centroids[1].coordinates[1] = 8;

    // Allocation et initialisation de clusters (à des fins de démonstration)
    num_clusters = 2;
    clusters = malloc(num_clusters * sizeof(point_t));
    clusters[0].dimension = 2;
    clusters[0].coordinates = malloc(clusters[0].dimension * sizeof(int64_t));
    clusters[0].coordinates[0] = 10;
    clusters[0].coordinates[1] = 11;
    clusters[0].clusterID = 0;

    clusters[1].dimension = 2;
    clusters[1].coordinates = malloc(clusters[1].dimension * sizeof(int64_t));
    clusters[1].coordinates[0] = 14;
    clusters[1].coordinates[1] = 12;
    clusters[1].clusterID = 1;
    printf("okay") ;
    
    params_t *input_params = malloc(sizeof(params_t));

    input_params->input_stream = fopen("input.txt", "r");
    input_params->output_stream = fopen(filename, "w");
    input_params->n_threads = 4;
    input_params->k = num_clusters;
    input_params->n_first_initialization_points = 5;
    input_params->quiet = false;
    input_params->squared_distance_func = NULL;
    input_params->dimension = 2;
    input_params->npoints = 2;
    input_params->points_list = clusters ; 

    printf("okay2") ;

    
    
     
    // Exécuter la fonction à tester
    int result = write_to_csv(input_params, initial_centroids, distortion, final_centroids);

    // Vérifier le résultat
    CU_ASSERT_EQUAL(result, 0);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Suite de tests pour write_to_csv", NULL, NULL);
    CU_add_test(suite, "Test de write_to_csv", Correct_execution);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
