#ifndef BINARY_PARSE_H
#define BINARY_PARSE_H

#include "common.h"
#include "point.h"
#include "params.h"

/**
 * @brief Parses binary data from the provided parameters.
 * 
 * @param params The parameters containing the binary data to parse.
 * @return uint32_t Returns 0 if successful, and a non-zero error code otherwise.
 */
uint32_t binary_parse(params_t* params);

/**
 * @brief Frees the memory allocated for a params_t structure.
 * 
 * @param params The params_t structure to free.
 */
void free_params_struct(params_t*);

#endif