#include "../headers/common.h"
#include "../headers/point.h"

inline point_ptr_t get_point(point_list_t list, uint32_t dim, size_t point_index) {
    return list + dim * point_index;
}
