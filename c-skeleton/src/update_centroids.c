#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/point.h"

int update_centroids(point_t* centroids, point_t* points, int k, int num_points){
    //Vérification des paramètres
    if(points == NULL||centroids == NULL || k < 0 || num_points < 0) {
        return -1;
    }
    
    int changed = 0;
    int64_t** sumPos = (int64_t**)malloc(k*sizeof(int64_t*)); //Somme des positions pour chaque cluster
    int* pByClust = (int*)calloc(k,sizeof(int)); //Nombre de points par cluster
    if(sumPos==NULL||pByClust==NULL){
        return -1;
    }
    
    //Allocation de mémoire pour chaque coordonée dans les sumPos
    for(int i=0; i<k;i++){
        sumPos[i] = (int64_t*)calloc(points[0].dimension, sizeof(int64_t));
        if(sumPos[i] == NULL){
            for(int j = 0; j < i; j++){
                free(sumPos[j]);
            }
            free(sumPos);
            free(pByClust);
            return -1;
        }
    }
    
    //Parcourir chaque point
    for(int i = 0; i<num_points; i++){
        //Ajouter les coordonnées du point à la somme du cluster
        for(int eachDim = 0; eachDim<points[0].dimension; eachDim++){
            if(sumPos[points[i].clusterID]==NULL){
            sumPos[points[i].clusterID][eachDim]=0;
            }
            sumPos[points[i].clusterID][eachDim]+=points[i].coordinates[eachDim];
        }
        //Augmenter le nombre de points du cluster
        pByClust[points[i].clusterID]++;    
    }

    //Calculer le nouveau centroïde
    for(int c = 0; c<k; c++){
        for(int eachDim = 0; eachDim<points[0].dimension; eachDim++){
            if(pByClust[c]==0){;}
            else{
                if(centroids[c].coordinates[eachDim]==sumPos[c][eachDim]/pByClust[c]){;} //Coordonnée du centroïde déjà au centre du cluster
                else{
                    centroids[c].coordinates[eachDim]=sumPos[c][eachDim]/pByClust[c]; //Mise à jour du centroïde
                    changed = 1;
                }
            }
        }
    }

    //Libération de la mémoire allouée
    for(int i = 0; i < k; i++){
        free(sumPos[i]);
    }
    free(sumPos);
    free(pByClust);

    return changed;
}
