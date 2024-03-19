#include "../headers/common.h"
#include "../headers/point.h"
#include "../headers/resultat_to_csv.h"
#include "../headers/params.h"



int write_to_csv(params_t* input , point_t *initial_centroids, int distortion, point_t *final_centroids) {
    FILE *output_file = input->output_stream ;
    uint32_t num_clusters = input->k ;
    uint64_t nbre_point = input->npoints ; 
    point_t *liste_cluster = input->points_list ;
    
     

    
    fprintf(output_file, "initialization centroids,distortion,centroids");
    if (num_clusters > 0)
        fprintf(output_file, ",clusters");
    fprintf(output_file, "\n");
    fprintf(output_file, "\n");

    // Écriture des lignes de données
        // Écriture des centroides d'initialisation
        fprintf(output_file, "\"[");
        
        for (uint32_t j = 0; j < initial_centroids[0].dimension; j++) {
            fprintf(output_file, "%ld", initial_centroids[0].coordinates[j]);
            if (j != initial_centroids[0].dimension - 1)
                fprintf(output_file, ", ");
        }
        fprintf(output_file, "]\",");

        // Écriture de la distortion
        fprintf(output_file, "%d,", distortion);
        // Ecriture des centroides finaux 
        fprintf(output_file, "\"[");
        for (uint32_t j = 0; j < final_centroids[0].dimension; j++) {
            fprintf(output_file, "%ld", final_centroids[0].coordinates[j]);
            if (j != final_centroids[0].dimension - 1)
                fprintf(output_file, ", ");
        }
         
        fprintf(output_file, "]\"");
        // Ecriture des clusters 
        if (num_clusters > 0) {
            fprintf(output_file, ",");
            fprintf(output_file, "\"[");
            
            int verif ; 
            for (int j = 0; j < nbre_point; j++) {
                int previous = liste_cluster[j].clusterID ;
                if (j+1 != nbre_point) {
                    if (liste_cluster[j+1].clusterID != previous) {
                        verif = 0 ;
                    }
                }
                // printf("%d",liste_cluster[0].clusterID) ; 
                // printf("%d",liste_cluster[1].clusterID) ; 


                // printf("okk") ;
                
                
                fprintf(output_file, "(");
                for (uint32_t k = 0; k < liste_cluster[j].dimension; k++) {
                    fprintf(output_file, "%ld", liste_cluster[j].coordinates[k]);
                    if (k != liste_cluster[j].dimension - 1)
                        fprintf(output_file, ", ");
                }
                // printf("Okay2") ;
                fprintf(output_file, ")");
                
                // printf("%d",verif) ; 
                if (verif == 0) {
                    fprintf(output_file, "],[");
                    verif = 1 ; 
                }
                else if (j != nbre_point -1 ){
                    fprintf(output_file, ",");}
                // if (j != num_clusters - 1){
                // fprintf(output_file, ", ");}
                
            }
            fprintf(output_file, "]\"");
        }

    fprintf(output_file, "\n");
    
    fclose(output_file); // Ferme le fichier
    
    return 0;
}
