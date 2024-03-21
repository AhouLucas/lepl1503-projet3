#ifndef POINT_H
#define POINT_H

#include "common.h"

typedef struct {
    uint32_t dimension;
    int64_t* coordinates;
    uint32_t clusterID;
} point_t;

/**
 * @brief Create a point object, using a malloc for coordinates.
 * 
 * @param dimension number of dimension of the point
 * @param coordinates Array of the coordinates, must be of size = dimension
 * @param clusterID the clusterID associated to the point
 * @return point_t
 */
point_t create_point(uint32_t dimension, int64_t* coordinates, uint32_t clusterID);

/**
 * @brief Free memory allocated for an array of points.
 * 
 * @param points Pointer to the first point of the array
 * @param n Size of the array
 */
void free_points(point_t* points, uint32_t n);

/**
 * @brief Make a copy of a point.
 * 
 * @param dest Memory address where the copy is saved
 * @param src Point to be copied
 * @return int 0 if successful, else 1 (malloc error)
 */
int copy_point(point_t* dest, const point_t* src);

/**
 * @brief Facilitates the print of points. Allow to "choose" level of details
 * 
 * @param p the point to be printed
 * @param detailed the level of details. 0, only coordinates ; 1, all attributes
 */
void print_point(point_t* p, uint32_t detailed);

/**
 * @brief Compare attributes of two points. Compatible with CU_ASSERT_TRUE()
 * 
 * @param p1 the first point
 * @param p2 the second point
 * @return int 1 if their attributes are equal, else 0
 */
int compare_point(point_t* p1, point_t* p2);

#endif //POINT_H
