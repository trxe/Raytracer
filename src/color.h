#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "rtweekend.h"

#include <iostream>

static Color RED = Color(0.8, 0.1, 0.5);
static Color BLUE = Color(0.5, 0.7, 1.0);
static Color YELLOW = Color(1.0, 1.0, 0.0);
static Color WHITE = Color(1.0, 1.0, 1.0);
static Color BLACK = Color(0.0, 0.0, 0.0);
const double min = 0.0;
const double max = 0.999;

/**
 * @brief Get an int array (RGB 0 - 255) from Color.
 * 
 * @param pixel_color 
 * @param samples_per_pixel 
 * @return int* 
 */
inline int* getIntColor(Color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples
    double scale = 1.0 / samples_per_pixel;
    r = sqrt(r * scale);
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    return new int[]{
        static_cast<int>(clamp(r, min, max) * 256),
        static_cast<int>(clamp(g, min, max) * 256),
        static_cast<int>(clamp(b, min, max) * 256),
    };

}

#endif