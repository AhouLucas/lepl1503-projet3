#include "headers/distance.h"
#include "headers/params.h"
#include "headers/common.h"
#include "headers/binary_parse.h"
#include "headers/combinations.h"
#include "headers/csv_write.h"
#include "headers/distortion.h"
#include "headers/kmeans.h"

void usage(const char *prog_name) {
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "    %s [-p n_combinations_points] [-n n_threads] [input_filename]\n", prog_name);
    fprintf(stderr, "    -k n_clusters (default value: 2): the number of clusters to compute\n");
    fprintf(stderr, "    -p n_combinations (default value: equal to k): consider the n_combinations first points present in the input to generate possible initializations for the k-means algorithm\n");
    fprintf(stderr, "    -n n_threads (default value: 4): sets the number of computing threads that will be used to execute the k-means algorithm\n");
    fprintf(stderr, "    -f output_file (default value: stdout): sets the filename on which to write the csv result\n");
    fprintf(stderr, "    -q quiet mode: does not output the clusters content (the \"clusters\" column is simply not present in the csv)\n");
    fprintf(stderr, "    -d distance (manhattan by default): can be either \"euclidean\" or \"manhattan\". Chooses the distance formula to use by the algorithm to compute the distance between the points\n");
}

static inline void parse_args(params_t *args, int argc, char *argv[]) {
    memset(args, 0, sizeof(params_t));    // set everything to 0 by default
    // the default values are the following, they will be changed depending on the arguments given to the program
    args->k = 2;
    args->n_first_initialization_points = args->k;
    args->n_threads = 1;
    args->output_stream = stdout;
    args->quiet = false;
    args->squared_distance_func = SQUARED_DISTANCE_MANHATTAN;
    int opt;
    int32_t temp;
    while ((opt = getopt(argc, argv, "n:p:k:f:d:q")) != -1) {
        switch (opt)
        {
            case 'n':
                temp = atoi(optarg);
                if (temp <= 0) {
                    if (args->output_stream != stdout) {
                        fclose(args->output_stream);
                    }

                    fprintf(stderr, "Wrong number of threads. Needs a positive integer, received \"%s\"\n", optarg);
                    exit(EXIT_FAILURE);
                } else {
                    args->n_threads = temp;
                }
                break;
            case 'p':
                temp = atoi(optarg);
                if (temp <= 0) {
                    if (args->output_stream != stdout) {
                        fclose(args->output_stream);
                    }

                    fprintf(stderr, "Wrong number of initialization points. Needs a positive integer, received \"%s\"\n", optarg);
                    exit(EXIT_FAILURE);
                } else {
                    args->n_first_initialization_points = temp;
                }
                break;
            case 'k':
                temp = atoi(optarg);
                if (temp <= 0) {
                    if (args->output_stream != stdout) {
                        fclose(args->output_stream);
                    }

                    fprintf(stderr, "Wrong k. Needs a positive integer, received \"%s\"\n", optarg);
                    exit(EXIT_FAILURE);
                } else {
                    args->k = temp;
                }
                break;
            case 'f':
                args->output_stream = fopen(optarg, "w");
                if (!args->output_stream) {
                    fprintf(stderr, "could not open output file %s: %s\n", optarg, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                break;
            case 'q':
                args->quiet = true;
                break;
            case 'd':
                if (strcmp("euclidean", optarg) == 0) {
                    args->squared_distance_func = SQUARED_DISTANCE_EUCLIDEAN;
                }
                break;
            case '?':
                if (args->output_stream != stdout) {
                    fclose(args->output_stream);
                }
                usage(argv[0]);
                exit(EXIT_SUCCESS);
            default:
                if (args->output_stream != stdout) {
                    fclose(args->output_stream);
                }
                usage(argv[0]);
                exit(EXIT_SUCCESS);
        }
    }

    if (optind == argc) {
        args->input_stream = stdin;
    } else {
        args->input_stream = fopen(argv[optind], "r");
        if (!args->input_stream) {
            if (args->output_stream != stdout) {
                fclose(args->output_stream);
            }

            fprintf(stderr, "could not open file %s: %s\n", argv[optind], strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    params_t params;   // allocate the args on the stack
    parse_args(&params, argc, argv);
    int result = EXIT_SUCCESS;

    if (params.n_first_initialization_points < params.k) {
        fprintf(stderr, "Cannot generate an instance of k-means with less initialization points than needed clusters: %"PRIu32" < %"PRIu32"\n",
                params.n_first_initialization_points, params.k);

        result = EXIT_FAILURE;
        goto cleanup;
    }
    
    if (binary_parse(&params) != 0) {
        result = EXIT_FAILURE;
        fprintf(stderr, "Failed parse binary file!\n");
        goto cleanup;
    }

    write_header_csv(&params);

    uint64_t n_comb = nbr_combinations(params.k, params.n_first_initialization_points);
    point_list_t initial_centroids = (point_list_t) malloc(sizeof(int64_t) * params.k * n_comb * params.dimension);

    if (initial_centroids == NULL) {
        free_params_struct(&params);

        fprintf(stderr, "Failed to allocate enought space for the initial centroids!\n");
        result = EXIT_FAILURE;

        goto cleanup;
    }

    if (generate_all_combinations(&params, initial_centroids) != 0) {
        free_params_struct(&params);

        fprintf(stderr, "Failed to generate point combinations!\n");
        result = EXIT_FAILURE;

        goto cleanup;

    }

    for (int i = 0; i < n_comb ; i++) { // TODO replace with combinations()
        write_row_head_csv(&params, initial_centroids+(i*params.k*params.dimension));
        params.centroids = initial_centroids+(i*params.k*params.dimension);
        kmeans(&params);
        write_row_tail_csv(&params, distortion(&params));
    }

    free(initial_centroids);
    free_params_struct(&params);

cleanup:
    if (params.input_stream != stdin) {
        fclose(params.input_stream);
    }
    if (params.output_stream != stdout) {
        fclose(params.output_stream);
    }

    return result;
}
