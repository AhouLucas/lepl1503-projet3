#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/point.h"

int update_centroids(point_t* centroids, point_t* points, int k, int num_points){
    if(points == NULL||centroids == NULL || k < 0 || num_points < 0) {
        return -1;
    }
    
    int changed = 0;
    int32_t dim = points[0].dimension;
    uint32_t* clusters = (uint32_t*)malloc(k*sizeof(uint32_t));
    int64_t** sumPos = (int64_t**)malloc(k*sizeof(int64_t*));
    int* pByClust = (int*)calloc(k,sizeof(int));
    if(clusters==NULL||sumPos==NULL||pByClust==NULL){
        return -1;
    }
    
    for(int i=0; i<k;i++){
        sumPos[i] = (int64_t*)calloc(dim, sizeof(int64_t));
        if(sumPos[i] == NULL){
            for(int j = 0; j < i; j++){
                free(sumPos[j]);
            }
            free(sumPos);
            free(clusters);
            free(pByClust);
            return -1;
        }
    }

    //Liste des clusters grâce aux centroids
    for(int c = 0; c<k; c++){
        clusters[c]=centroids[c].clusterID;
    }
    
    //Parcourir chaque point
    for(int i = 0; i<num_points; i++){
        //Vérifier pour chaque cluster si c'est celui du point
        for(int clusterIndex = 0; clusterIndex<k; clusterIndex++){
            if(points[i].clusterID==clusters[clusterIndex]){
                //Ajouter les coordonnées du point à la somme du cluster
                for(int eachDim = 0; eachDim<dim; eachDim++){
                    if(sumPos[clusterIndex]==NULL){
                    sumPos[clusterIndex][eachDim]=0;
                    }
                    sumPos[clusterIndex][eachDim]+=points[i].coordinates[eachDim];
                }
                //Augmenter le nombre de points du cluster
                pByClust[clusterIndex]++;
            }
        }
    }

    //Calculer le nouveau centroide
    for(int c = 0; c<k; c++){
        for(int eachDim = 0; eachDim<dim; eachDim++){
            if(pByClust[c]==0){;}
            else{
                if(centroids[c].coordinates[eachDim]==sumPos[c][eachDim]/pByClust[c]){;}
                else{
                    centroids[c].coordinates[eachDim]=sumPos[c][eachDim]/pByClust[c];
                    changed = 1;
                }
            }
        }
    }
    for(int i = 0; i < k; i++){
        free(sumPos[i]);
    }

    free(clusters);
    free(sumPos);
    free(pByClust);

    return changed;
}
