#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <memory>
#include <limits>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Math constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility function 

inline double degrees_to_radians(int deg) {
    return deg * pi / 180;
}

#include "ray.h"
#include "vec3.h"

#endif