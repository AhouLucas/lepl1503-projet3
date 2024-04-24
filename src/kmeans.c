#include "../headers/kmeans.h"
#include "../headers/closest_centroids.h"
#include "../headers/update_centroids.h"

typedef struct {
    params_t* params;
    size_t start_idx;
    size_t end_idx;
} thread_data_t;

void thread_function(void* args) {
    thread_data_t* data = (thread_data_t*)args;
}

void kmeans(params_t *params) {
    int has_changed = 1;

    closest_centroid(params);

    while (has_changed) {
        has_changed = update_centroids(params);
        closest_centroid(params);
    }
}