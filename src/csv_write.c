#include "../headers/csv_write.h"

static int cmp_points(const void *a, const void *b) {
    point_t p1 = *(point_t*)a;
    point_t p2 = *(point_t*)b;

    return p1.clusterID - p2.clusterID;
}

void write_header_csv(params_t *params) {
    fputs("initialization centroids,distortion,centroids", params->output_stream);
    
    if (!params->quiet) {
        fputs(",clusters\n", params->output_stream);
    } else {
        fputc('\n', params->output_stream);
    }
}

inline static void write_point(FILE *stream, point_t point) {
    putc('(', stream);

    for (int i = 0; i < point.dimension; i++) {
        fprintf(stream, "%ld", point.coordinates[i]);

        if (i < point.dimension - 1) {
            fputs(", ", stream);
        }
    }

    putc(')', stream);
}

void write_point_list(FILE *stream, point_t *points, size_t num_points) {
    fputs("\"[", stream);

    for (int i = 0; i < num_points; i++) {
        point_t point = points[i];

        write_point(stream, point);

        if (i < num_points - 1) {
            fputs(", ", stream);
        }
    }

    fputs("]\"", stream);
}

void write_row_head_csv(params_t *params, point_t *initialization_centroids) {
    write_point_list(params->output_stream, initialization_centroids, params->k);
}

void write_row_tail_csv(params_t *params, uint64_t distortion) {
    fprintf(params->output_stream, ",%ld,", distortion);
    
    write_point_list(params->output_stream, params->centroids, params->k);
    
    if (!params->quiet) {
        qsort(params->points_list, params->npoints, sizeof(point_t), cmp_points);

        int last_cluster_id = -1;
        bool is_first_cluster = true;

        fputs(",\"[[", params->output_stream);

        for (size_t i = 0; i < params->npoints; i++) {
            point_t point = params->points_list[i];

            if (last_cluster_id != point.clusterID) {
                if (!is_first_cluster) {
                    fputs("], [", params->output_stream);
                } else {
                    is_first_cluster = false;
                }
                last_cluster_id = point.clusterID;
            } else {
                fputs(", ", params->output_stream);
            }

            write_point(params->output_stream, point);
        }

        fputs("]]\"\n", params->output_stream);
    } else {
        fputc('\n', params->output_stream);
    }
}