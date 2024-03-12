#include "common.h"

#include "../headers/update_centroids.h"
#include "../headers/point.h"

// Pas terminer vous inquiéter pas 

int resultat_to_csv(point_t* initial_centroids, int distortion,point_t* final_centroids,point_t** int clusters,int write_cluster){
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return 0;
    }
    fprintf(file, "initialization centroids,distortion,centroids");
    if (write_clusters) {
        fprintf(file, ",clusters");
    }
    if (write_clusters) {
        fprintf(file, ",clusters");
    }
    fprintf(file, "\n");
    for (int i = 0; i < num_points; i++) {
        fprintf(file, "%s,%d,%s", 
                list_to_string(initial_centroids[i]),
                distortion,
                list_to_string(final_centroids[i]));
        if (write_clusters) {
            fprintf(file, ",%s", list_to_string(clusters[i]));
        }
        fprintf(file, "\n");
    }

    fclose(file); // Fermer le fichier
    return 1;
}



