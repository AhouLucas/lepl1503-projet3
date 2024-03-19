#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/point.h"
#include "../headers/params.h"

int update_centroids(params_t* params){
    //Vérification des paramètres
    if(params->points_list == NULL||params->centroids == NULL || params->k < 0 || params->npoints < 0) {
        return -1;
    }
    
    int changed = 0;
    int64_t** sumPos = (int64_t**)malloc(params->k*sizeof(int64_t*)); //Somme des positions pour chaque cluster
    int* pByClust = (int*)calloc(params->k,sizeof(int)); //Nombre de points par cluster
    if(sumPos==NULL||pByClust==NULL){
        return -1;
    }
    
    //Allocation de mémoire pour chaque coordonée dans les sumPos
    for(int i=0; i<params->k;i++){
        sumPos[i] = (int64_t*)calloc(params->dimension, sizeof(int64_t));
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
    for(int i = 0; i<params->npoints; i++){
        //Ajouter les coordonnées du point à la somme du cluster
        for(int eachDim = 0; eachDim<params->dimension; eachDim++){
            if(sumPos[params->points_list[i].clusterID]==NULL){
            sumPos[params->points_list[i].clusterID][eachDim]=0;
            }
            sumPos[params->points_list[i].clusterID][eachDim]+=params->points_list[i].coordinates[eachDim];
        }
        //Augmenter le nombre de points du cluster
        pByClust[params->points_list[i].clusterID]++;    
    }

    //Calculer le nouveau centroïde
    for(int c = 0; c<params->k; c++){
        for(int eachDim = 0; eachDim<params->dimension; eachDim++){
            if(pByClust[c]==0){;}
            else{
                if(params->centroids[c].coordinates[eachDim]==sumPos[c][eachDim]/pByClust[c]){;} //Coordonnée du centroïde déjà au centre du cluster
                else{
                    params->centroids[c].coordinates[eachDim]=sumPos[c][eachDim]/pByClust[c]; //Mise à jour du centroïde
                    changed = 1;
                }
            }
        }
    }

    //Libération de la mémoire allouée
    for(int i = 0; i < params->k; i++){
        free(sumPos[i]);
    }
    free(sumPos);
    free(pByClust);

    return changed;
}
