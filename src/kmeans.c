#include "../headers/kmeans.h"
#include "../headers/closest_centroids.h"
#include "../headers/update_centroids.h"

void kmeans(params_t *params) {
    int has_changed = 1;

    while (has_changed) {
        has_changed = closest_centroid(params);
        update_centroids(params);
    }
}