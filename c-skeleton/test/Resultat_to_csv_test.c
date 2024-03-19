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
int npoints ; 

void Correct_execution() {
    const char *filename = "output.csv"; // Nom du fichier de sortie
    num_clusters = 3 ; 
    npoints = 3 ; 

    

    // Initialisation des centroides initiaux et finaux en tant que tableaux de point_t
    // Initialisation des centroides initiaux et finaux en tant que tableaux de point_t
    initial_centroids = malloc(num_clusters * sizeof(point_t));
    final_centroids = malloc(num_clusters * sizeof(point_t));

    for (int i = 0; i < num_clusters; i++) {
        initial_centroids[i].dimension = 2;
        initial_centroids[i].coordinates = malloc(initial_centroids[i].dimension * sizeof(long));
        initial_centroids[i].coordinates[0] = rand() % 20;
        initial_centroids[i].coordinates[1] = rand() % 20;

        final_centroids[i].dimension = 2;
        final_centroids[i].coordinates = malloc(final_centroids[i].dimension * sizeof(long));
        final_centroids[i].coordinates[0] = rand() % 20;
        final_centroids[i].coordinates[1] = rand() % 20;
    }

    // Allocation et initialisation de clusters (à des fins de démonstration)
    clusters = (point_t*) malloc(npoints * sizeof(point_t));

    for(int i = 0 ; i <  npoints ; i++) {
        clusters[i].dimension = 2 ; 
        clusters[i].coordinates = malloc(clusters[0].dimension * sizeof(int64_t));
        clusters[i].coordinates[0] = rand() % 20;
        clusters[i].coordinates[1] = rand() % 20;
        clusters[i].clusterID = rand() % 2;
    }
    
    
    
    
    params_t *input_params = malloc(sizeof(params_t));

    input_params->input_stream = fopen("input.txt", "r");
    input_params->output_stream = fopen(filename, "w");
    input_params->n_threads = 4;
    input_params->k = num_clusters;
    input_params->n_first_initialization_points = 5;
    input_params->quiet = false;
    input_params->squared_distance_func = NULL;
    input_params->dimension = 2;
    input_params->npoints = npoints;
    input_params->points_list = clusters ; 
    


    
    
     
    // Exécuter la fonction à tester
    int result = write_to_csv(input_params, initial_centroids, distortion, final_centroids);

    // Vérifier le résultat
    CU_ASSERT_EQUAL(result, 0);

    for (int i = 0; i < num_clusters; ++i) {
        free(initial_centroids[i].coordinates);
        free(final_centroids[i].coordinates);
    }
    free(initial_centroids);
    free(final_centroids);
    for (int i = 0; i < npoints; ++i) {
        free(clusters[i].coordinates);
    }
    free(clusters);
    
    free(input_params);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Suite de tests pour write_to_csv", NULL, NULL);
    CU_add_test(suite, "Test de write_to_csv", Correct_execution);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
