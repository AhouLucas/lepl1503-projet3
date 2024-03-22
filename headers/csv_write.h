#ifndef CSV_WRITE
#define CSV_WRITE

#include "common.h"
#include "point.h"
#include "params.h"


/**
 * @brief Writes the header row to the CSV output.
 * 
 * This function writes the header row to the CSV output stream specified in the params structure.
 * The header row includes the column names: "initialization centroids", "distortion", and "centroids".
 * If the quiet flag is not set in the params structure, it also includes the "clusters" column.
 * 
 * @param params The parameters containing the output stream and the quiet flag.
 */
void write_header_csv(params_t *params);

/**
 * @brief Writes the initialization centroids to the CSV output.
 * 
 * This function writes the initialization centroids to the CSV output stream specified in the params structure.
 * 
 * @param params The parameters containing the output stream.
 * @param initialization_centroids The initialization centroids to write.
 */
void write_row_head_csv(params_t *params, point_list_t initialization_centroids);

/**
 * @brief Writes the distortion and centroids to the CSV output.
 * 
 * This function writes the distortion and centroids to the CSV output stream specified in the params structure.
 * If the quiet flag is not set in the params structure, it also writes the clusters.
 * 
 * @param params The parameters containing the output stream, the distortion, the centroids, and the quiet flag.
 * @param distortion The distortion to write.
 */
void write_row_tail_csv(params_t *params, uint64_t distortion);


#endif // CSV_WRITE