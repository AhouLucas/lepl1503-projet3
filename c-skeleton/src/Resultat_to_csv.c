#include "../headers/common.h"


#include "../headers/point.h"
#include "../headers/resultat_to_csv.h"



int write_to_csv(const char *filename, point_t *initial_centroids, int distortion, point_t *final_centroids, point_t ***clusters, int num_clusters) {
    FILE *output_file = fopen(filename, "w"); 

    if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    
    fprintf(output_file, "initialization centroids,distortion,centroids");
    if (num_clusters > 0)
        fprintf(output_file, ",clusters");
    fprintf(output_file, "\n");
    fprintf(output_file, "\n");

    // Écriture des lignes de données
    for (int i = 0; i < num_clusters; i++) {
        // Écriture des centroides d'initialisation
        fprintf(output_file, "\"[");
        for (uint32_t j = 0; j < initial_centroids[i].dimension; j++) {
            fprintf(output_file, "%ld", initial_centroids[i].coordinates[j]);
            if (j != initial_centroids[i].dimension - 1)
                fprintf(output_file, ", ");
        }
        fprintf(output_file, "]\",");

        // Écriture de la distortion
        fprintf(output_file, "%d,", distortion);

        fprintf(output_file, "\"[");
        for (uint32_t j = 0; j < final_centroids[i].dimension; j++) {
            fprintf(output_file, "%ld", final_centroids[i].coordinates[j]);
            if (j != final_centroids[i].dimension - 1)
                fprintf(output_file, ", ");
        }
        fprintf(output_file, "]\"");

        if (num_clusters > 0) {
            fprintf(output_file, ",");
            fprintf(output_file, "\"[");
            for (int j = 0; j < num_clusters; j++) {
                fprintf(output_file, "[");
                for (uint32_t k = 0; k < (*clusters)[i][j].dimension; k++) {
                    fprintf(output_file, "%ld", (*clusters)[i][j].coordinates[k]);
                    if (k != (*clusters)[i][j].dimension - 1)
                        fprintf(output_file, ", ");
                }
                fprintf(output_file, "]");
                if (j != num_clusters - 1)
                    fprintf(output_file, ", ");
            }
            fprintf(output_file, "]\"");
        }

        fprintf(output_file, "\n");
    }
    fclose(output_file); // Ferme le fichier

    return 0;
}
