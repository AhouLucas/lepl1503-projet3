#include <assert.h>

#include "../headers/kmeans.h"
#include "../headers/closest_centroids.h"
#include "../headers/update_centroids.h"

void *thread_function(void* args) {
    thread_data_t* data = (thread_data_t*)args;

    while (true) {
        closest_centroid(data->params, data->start_idx, data->end_idx, data->partial_sum);
        pthread_barrier_wait(data->barrier);
    }

    pthread_exit(NULL);
}

void kmeans(params_t *params) {
    // greedy approach
    int changed = 1;

    pthread_t *threads = malloc(sizeof(pthread_t) * (params->n_threads - 1));
    uint32_t *thread_sums = calloc(params->k * (params->n_threads - 1), sizeof(uint32_t));

    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, NULL, params->n_threads);

    uint64_t rem = params->npoints % (params->n_threads-1);
    uint64_t range = params->npoints / (params->n_threads-1);
    uint64_t last_end_idx = 0;
    for (int i = 0; i < params->n_threads-1; i++) {
        int bonus = 0;

        if (rem > 0) {
            rem--;
            bonus = 1;
        }

        thread_data_t data = {
            .start_idx = last_end_idx,
            .end_idx = range * i + bonus,
            .params = params,
            .partial_sum = thread_sums + params->k * i
        };

        printf("%ld - %ld", data.start_idx, data.end_idx);

        pthread_create(threads + i, NULL, thread_function, &data);
    }
    
    while (changed) {
        pthread_barrier_wait(&barrier);

        memset(params->cluster_sizes, 0, params->k * sizeof(uint32_t));

        // perform reduction
        for (int i = 0; i < params->n_threads - 1; i++) {
            for (int j = 0; j < params->k; j++) {
                params->cluster_sizes[j] += thread_sums[(params->k * i) + j];
            }
        }

        changed = update_centroids(params);
    }

    for (int i = 0; i < params->n_threads - 1; i++) {
        pthread_cancel(threads[i]);
    }

    pthread_barrier_destroy(&barrier);
    free(threads);
    free(thread_sums);
}