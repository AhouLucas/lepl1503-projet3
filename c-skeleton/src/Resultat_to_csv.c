#include "../headers/common.h"


#include "../headers/point.h"
#include "../headers/resultat_to_csv.h"



int write_to_csv(const char *filename, tuple_t *initial_centroids, int distortion, tuple_t *final_centroids, tuple_t ***clusters, int num_clusters) {
    FILE *output_file = fopen(filename, "w"); // Ouvre le fichier en écriture (crée le fichier s'il n'existe pas)

    if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Écriture de l'en-tête
    fprintf(output_file, "initialization centroids,distortion,centroids");
    if (num_clusters > 0)
        fprintf(output_file, ",clusters");
    fprintf(output_file, "\n");
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
    fclose(output_file); // Ferme le fichier

    
     // Ferme le fichier
    return 0 ; 
}



