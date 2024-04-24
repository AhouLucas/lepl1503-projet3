#include <assert.h>

#include "../headers/kmeans.h"
#include "../headers/closest_centroids.h"
#include "../headers/update_centroids.h"

pthread_barrier_t barrier;
pthread_barrier_t barrier2;

void *thread_function(void *args)
{
    thread_data_t *data = (thread_data_t *)args;

    while (!(*data->cancel))
    {
        closest_centroid(data->params, data->start_idx, data->end_idx, data->partial_sum);
        pthread_barrier_wait(&barrier);
        pthread_barrier_wait(&barrier2);
    }

    free(data);
    pthread_exit(NULL);
}

void kmeans(params_t *params)
{
    if (params->n_threads > 1)
    {
        // greedy approach
        int changed = 1;
        bool cancel = false;

        pthread_t *threads = malloc(sizeof(pthread_t) * (params->n_threads - 1));
        uint32_t *thread_sums = calloc(params->k * (params->n_threads - 1), sizeof(uint32_t));

        assert(thread_sums != NULL && threads != NULL);

        assert(pthread_barrier_init(&barrier, NULL, params->n_threads) == 0);
        assert(pthread_barrier_init(&barrier2, NULL, params->n_threads) == 0);

        uint64_t rem = params->npoints % (params->n_threads - 1);
        uint64_t range = params->npoints / (params->n_threads - 1);
        uint64_t last_end_idx = 0;

        memset(params->cluster_sizes, 0, params->k * sizeof(uint32_t));
        memset(params->cluster_means, 0, params->k * params->dimension * sizeof(int64_t));

        for (int i = 0; i < (params->n_threads - 1); i++)
        {
            int bonus = 0;

            if (rem > 0)
            {
                rem--;
                bonus = 1;
            }

            thread_data_t *data = malloc(sizeof(thread_data_t));
            assert(data != NULL);

            data->start_idx = last_end_idx;
            data->end_idx = last_end_idx + range + bonus;
            data->params = params;
            data->partial_sum = thread_sums + params->k * i;
            data->cancel = &cancel;
            data->barrier = &barrier;

            last_end_idx = data->end_idx;

            pthread_create(threads + i, NULL, thread_function, data);
        }

        while (changed)
        {
            pthread_barrier_wait(&barrier);
            // perform reduction
            for (int i = 0; i < params->n_threads - 1; i++)
            {
                for (int j = 0; j < params->k; j++)
                {
                    params->cluster_sizes[j] += thread_sums[(params->k * i) + j];
                }
            }

            changed = update_centroids(params);

            // printf("centroid: [");
            // for (int i = 0; i < params->k; i++)
            // {
            //     printf("%ld", params->centroids[i]);
            //     if (i < params->k - 1)
            //     {
            //         printf(", ");
            //     }
            // }
            // printf("]\n");

            memset(params->cluster_sizes, 0, params->k * sizeof(uint32_t));
            memset(params->cluster_means, 0, params->k * params->dimension * sizeof(int64_t));

            cancel = !changed;

            pthread_barrier_wait(&barrier2);
        }

        for (int i = 0; i < params->n_threads - 1; i++)
        {
            pthread_join(threads[i], NULL);
        }

        pthread_barrier_destroy(&barrier);
        pthread_barrier_destroy(&barrier2);
        free(threads);
        free(thread_sums);
    }
    else
    {
        int has_changed = 1;

        memset(params->cluster_sizes, 0, params->k * sizeof(uint32_t));
        memset(params->cluster_means, 0, params->k * params->dimension * sizeof(int64_t));
        closest_centroid(params, 0, params->npoints, params->cluster_sizes);

        while (has_changed)
        {
            has_changed = update_centroids(params);
            memset(params->cluster_sizes, 0, params->k * sizeof(uint32_t));
            memset(params->cluster_means, 0, params->k * params->dimension * sizeof(int64_t));
            closest_centroid(params, 0, params->npoints, params->cluster_sizes);
        }
    }
}