#include "../headers/csv_write.h"

void write_header_csv(params_t *params) {
    fputs("initialization centroids,distortion,centroids", params->output_stream);
    
    if (!params->quiet) {
        fputs(",clusters\n", params->output_stream);
    } else {
        fputc('\n', params->output_stream);
    }
}

inline static void write_point(FILE *stream, point_ptr_t point, uint32_t dim) {
    putc('(', stream);

    for (int i = 0; i < dim; i++) {
        fprintf(stream, "%ld", point[i]);

        if (i < dim - 1) {
            fputs(", ", stream);
        }
    }

    putc(')', stream);
}

void write_point_list(FILE *stream, point_list_t points, size_t num_points, uint32_t dim) {
    fputs("\"[", stream);

    for (int i = 0; i < num_points; i++) {
        point_ptr_t point = get_point(points, dim, i);

        write_point(stream, point, dim);

        if (i < num_points - 1) {
            fputs(", ", stream);
        }
    }

    fputs("]\"", stream);
}

void write_row_head_csv(params_t *params, point_list_t initialization_centroids) {
    write_point_list(params->output_stream, initialization_centroids, params->k, params->dimension);
}

void write_row_tail_csv(params_t *params, uint64_t distortion) {
    fprintf(params->output_stream, ",%lu,", distortion);

    write_point_list(params->output_stream, params->centroids, params->k, params->dimension);

    if (!params->quiet) {
        fputs(",\"[[", params->output_stream);

        for (size_t i = 0; i < params->k; i++) {
            bool first = true;
            for (size_t j = 0; j < params->npoints; j++) {
                if (params->cluster_ids[j] == i) {
                    if (!first) {
                        fputs(", ", params->output_stream);
                    }

                    write_point(params->output_stream, get_point(params->points_list, params->dimension, j), params->dimension);
                    first = false;
                }
            }

            if (i < params->k - 1) {
                fputs("], [", params->output_stream);
            }
        }

        fputs("]]\"\n", params->output_stream);
    } else {
        fputc('\n', params->output_stream);
    }
}