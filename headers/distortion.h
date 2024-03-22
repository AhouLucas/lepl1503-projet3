#ifndef DISTORTION_H
#define DISTORTION_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "params.h"

/**
 * @brief Computes and returns the distortion of the clustering
 * 
 * @param params Struct containing all the parameters of the clustering
 * @return uint64_t Value of the distortion or -1 if the parameters are invalid
 */
uint64_t distortion(params_t* params);

#endif // DISTORTION_H