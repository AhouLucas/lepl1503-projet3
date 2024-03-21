#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/point.h"
#include "../headers/params.h"

int update_centroids(params_t* params){
    int k =params->k;
    int num_points = params->npoints;
    point_list_t points = params->points_list;
    point_list_t centroids = params->centroids;
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
    for(int i = 0; i<num_points; i++){
        //Ajouter les coordonnées du point à la somme du cluster
        for(int eachDim = 0; eachDim < params->dimension; eachDim++){
            if(sumPos[params->cluster_id[i]]==NULL){
            sumPos[params->cluster_id[i]][eachDim]=0;
            }
            sumPos[params->cluster_id[i]][eachDim]+= get_point(points, params->dimension, i)[eachDim];
        }
        //Augmenter le nombre de points du cluster
        pByClust[params->cluster_id[i]]++;    
    }

    //Calculer le nouveau centroïde
    for(int c = 0; c<k; c++){
        for(int eachDim = 0; eachDim<params->dimension; eachDim++){
            if(pByClust[c]!=0){
                if (get_point(centroids, params->dimension, c)[eachDim] == sumPos[c][eachDim]/pByClust[c]){;} //Coordonnée du centroïde déjà au centre du cluster
                else{
                    get_point(centroids, params->dimension, c)[eachDim] = sumPos[c][eachDim]/pByClust[c]; //Mise à jour du centroïde
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
