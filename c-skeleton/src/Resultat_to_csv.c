#include "common.h"

#include "../headers/update_centroids.h"
#include "../headers/point.h"

// Pas terminer vous inquiéter pas 

void write_to_csv(FILE *output_file, tuple_t *initial_centroids, int distortion, tuple_t *final_centroids, tuple_t ***clusters, int num_clusters) {
    // Écriture de l'en-tête
    fprintf(output_file, "initialization centroids,distortion,centroids");
    if (num_clusters > 0)
        fprintf(output_file, ",clusters");
    fprintf(output_file, "\n");

    // Écriture des lignes de données
    for (int i = 0; i < num_clusters; i++) {
        // Écriture des centroides d'initialisation
        fprintf(output_file, "[(%ld, %ld)],", initial_centroids[i].x, initial_centroids[i].y);

        // Écriture de la distortion
        fprintf(output_file, "%d,", distortion);

        // Écriture des centroides finaux
        fprintf(output_file, "[(%ld, %ld)]", final_centroids[i].x, final_centroids[i].y);

        // Écriture des clusters
        if (num_clusters > 0) {
            fprintf(output_file, ",");
            fprintf(output_file, "[");
            for (int j = 0; j < num_clusters; j++) {
                fprintf(output_file, "[(%ld, %ld)]", (*clusters)[i][j].x, (*clusters)[i][j].y);
                if (j != num_clusters - 1)
                    fprintf(output_file, ", ");
            }
            fprintf(output_file, "]");
        }

        fprintf(output_file, "\n");
    }
}



