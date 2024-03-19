#ifndef CSV_WRITE
#define CSV_WRITE

#include "common.h"
#include "point.h"
#include "params.h"


/**
 * @brief Writes the header to a csv file
 * 
 * @param csv_file Pointer to the file to write to
 * @param quietMode If true, the last column (which corresponds to the list of clusters) will not be written
 * @return int 0 if successful, -1 if an error occurred
 */
int write_header_csv(FILE* stream, bool quietMode);
/**
 * @brief Writes a line to a csv file every time it is called
 * 
 * @param csv_file Pointer to the file to write to
 * @param initialization_centroids Array of centroids used for initialization
 * @param distortion Value of distortion after the last iteration
 * @param final_centroids Array of centroids after the last iteration
 * @param points Array of points which have been clustered
 * @param quietMode If true, the last column (which corresponds to the list of clusters) will not be written
 * @return int 0 if successful, -1 if an error occurred
 */
int write_row_csv(FILE* stream, point_t* initialization_centroids, uint64_t distortion, params_t *params);


#endif // CSV_WRITE