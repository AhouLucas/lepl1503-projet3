#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/point.h"
#include "../headers/binary_parse.h"

params_t* binary_parse(FILE *file) {
    params_t* parameters = (params_t*) malloc(sizeof(params_t));

    if(parameters == NULL) {
        printf("!! Couldn't malloc for struct params_t !! \n In binary_parse");
        return NULL;
    }
    
    uint32_t dim = 0;
    size_t e_dimension = fread(&dim, sizeof(uint32_t), 1, file);
    if(e_dimension != 1) {
        printf("Couldn't read the dimension \n In binary_parse");
        return NULL;
    }
    dim = be32toh(dim);
    parameters->dimension = dim;

    uint64_t n = 0;
    size_t e_npoints = fread(&n, sizeof(uint64_t), 1, file);
    if(e_npoints != 1) {
        printf("Couldn't read the number of points \n In binary_parse");
        return NULL;
    }
    n = be64toh(n);
    parameters->npoints = n;

    point_t* points = (point_t*) malloc(n * sizeof(point_t));
    if(points == NULL) {
        printf("Couldn't malloc for points \n In binary_parse");
        return NULL;
    }
    parameters->points_list = points;

    int offset = 0;
    while(offset < n) {
        point_t point;
        int64_t* coordinates = (int64_t*) malloc(dim * sizeof(int64_t));
        
        size_t e_coordinates = fread(coordinates, sizeof(int64_t), dim, file);
        if(e_coordinates != dim) {
            printf("There was an error while parsing points \n In binary_parsing");
            return NULL;
        }

        int i = 0;
        while(i<dim) {
            coordinates[i] = (int64_t) be64toh((uint64_t) coordinates[i]);
            i++;
        }

        point.dimension = dim;
        point.clusterID = 0;
        point.coordinates = coordinates;

        parameters->points_list[offset] = point;
        offset++;
    }
    
    return parameters;
}

void free_params_struct(params_t* parameters) {
    uint64_t n = parameters->npoints;
    int i = 0;
    while(i < n) {
        free(parameters->points_list[i].coordinates);
        i++;
    }
    free(parameters->points_list);
    free(parameters);
}