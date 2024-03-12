#include "../headers/common.h"
#include "../headers/update_centroids.h"
#include "../headers/point.h"

int update_centroids(point_t* centroids, point_t* points, int k, int num_points){
    if(points == NULL||centroids == NULL || k == 0) {
        return -1;
    }
    int32_t dim = points->dimension;

    uint32_t* clusters = (uint32_t*)malloc(k*sizeof(uint32_t));
    int64_t** sumPos = (int64_t**)malloc(k*sizeof(int64_t[dim]));
    int* pByClust = (int*)malloc(k*sizeof(int));
    if(clusters==NULL||sumPos==NULL||pByClust==NULL){
        return -1;
    }

    //Faire une liste des clusters grâce aux centroids
    for(int c = 0; c<k; c++){
        clusters[c]=centroids[c].clusterID;
    }

    for(int i = 0; i<num_points; i++){
        for(int clusterIndex = 0; clusterIndex<k; clusterIndex++){
            if(points[i].clusterID==clusters[clusterIndex]){
                for(int eachDim = 0; eachDim<dim; eachDim++){
                    sumPos[clusterIndex][eachDim]+=points[i].coordinates[eachDim];
                }
                pByClust[clusterIndex]++;
            }
        }
    }
    for(int c = 0; c<k; c++){
        for(int eachDim = 0; eachDim<dim; eachDim++){
                    centroids[c].coordinates[eachDim]=sumPos[c][eachDim]/pByClust[c];
                }
    }

    return 0;
}
