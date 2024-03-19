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

int write_row_csv(FILE* stream, point_t* initialization_centroids, uint64_t distortion, point_t* final_centroids, point_t* points, size_t num_points, bool quietMode) {
    // TODO as a param
    int k = 3;

    write_point_list(stream, initialization_centroids, k);

    fprintf(stream, ",%d,", distortion);

    write_point_list(stream, final_centroids, k);

    if (!quietMode) {
        qsort(points, num_points, sizeof(point_t), cmp_points);

        int last_cluster_id = -1;
        fputs(",\"[[", stream);

        for (size_t i = 0; i < num_points; i++) {
            point_t point = points[i];

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