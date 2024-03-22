#include "../headers/common.h"
#include "../headers/point.h"
#include "../headers/binary_parse.h"

uint32_t binary_parse(params_t* params) {
    
    uint32_t dim = 0;
    size_t e_dimension = fread(&dim, sizeof(uint32_t), 1, params->input_stream);
    if(e_dimension != 1) {
        printf("Couldn't read the dimension \n In binary_parse");
        return 1;
    }
    dim = be32toh(dim);
    params->dimension = dim;

    uint64_t n = 0;
    size_t e_npoints = fread(&n, sizeof(uint64_t), 1, params->input_stream);
    if(e_npoints != 1) {
        printf("Couldn't read the number of points \n In binary_parse");
        return 2;
    }
    n = be64toh(n);
    params->npoints = n;

    point_list_t points = (point_list_t)malloc(n * dim * sizeof(int64_t));

    if (points == NULL) {
        return -1;
    }

    params->cluster_ids = calloc(n * dim, sizeof(uint32_t));

    if(params->cluster_ids == NULL) {
        free(points);
        return -1;
    }

    params->cluster_sizes = malloc(n * dim * sizeof(uint32_t));

    if (params->cluster_sizes == NULL) {
        free(points);
        free(params->cluster_ids);
        return -1;
    }

    params->points_list = points;

    uint64_t offset = 0;
    while(offset < n) {
        point_ptr_t coordinates = get_point(points, dim, offset);
        size_t e_coordinates = fread(coordinates, sizeof(int64_t), dim, params->input_stream);
        if (e_coordinates != dim) {
            printf("There was an error while parsing points \n In binary_parsing");
            return 4;
        }

        uint32_t i = 0;
        while(i<dim) {
            coordinates[i] = (int64_t) be64toh((uint64_t) coordinates[i]);
            i++;
        }
        offset++;
    }
    
    return 0;
}

void free_params_struct(params_t* parameters) {
    free(parameters->cluster_ids);
    free(parameters->cluster_sizes);
    free(parameters->points_list);
}