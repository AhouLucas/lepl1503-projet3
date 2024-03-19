#include "../headers/csv_write.h"

static int cmp_points(const void *a, const void *b) {
    point_t p1 = *(point_t*)a;
    point_t p2 = *(point_t*)b;

    return p1.clusterID - p2.clusterID;
}

int write_header_csv(FILE* stream, bool quietMode) {
    fputs("initialization centroids,distortion,centroids", stream);
    
    if (!quietMode) {
        fputs(",clusters\n", stream);
    } else {
        fputc('\n', stream);
    }
}

inline static void write_point(FILE* stream, point_t point) {
    putc('(', stream);

    for (int i = 0; i < point.dimension; i++) {
        fprintf(stream, "%d", point.coordinates[i]);

        if (i < point.dimension - 1) {
            fputs(", ", stream);
        }
    }

    putc(')', stream);
}

inline static void write_point_list(FILE* stream, point_t *points, size_t num_points) {
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

int write_row_csv(FILE* stream, point_t* initialization_centroids, uint64_t distortion, params_t *params) {
    write_point_list(stream, initialization_centroids, params->k);

    fprintf(stream, ",%d,", distortion);

    write_point_list(stream, params->centroids, params->k);

    if (!params->quiet) {
        qsort(params->points_list, params->npoints, sizeof(point_t), cmp_points);

        int last_cluster_id = -1;
        fputs(",\"[[", stream);

        for (size_t i = 0; i < params->npoints; i++) {
            point_t point = params->points_list[i];

            if (last_cluster_id != point.clusterID) {
                fputs("], [", stream);
                last_cluster_id = point.clusterID;
            } else {
                fputs(", ", stream);
            }

            write_point(stream, point);
        }

        fputs("]]\"\n", stream);
    } else {
        fputc('\n', stream);
    }
}