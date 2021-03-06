#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <memory>
#include <limits>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;
using std::rand;

// Math constants
const double INFTY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility function 

inline double degrees_to_radians(int deg) {
    return deg * PI / 180;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max-min) * random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif