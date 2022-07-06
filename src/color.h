#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "rtweekend.h"

#include <iostream>

Color red = Color(0.8, 0.1, 0.5);
Color blue = Color(0.5, 0.7, 1.0);
Color yellow = Color(1.0, 1.0, 0.0);
Color white = Color(1.0, 1.0, 1.0);
Color black = Color(0.0, 0.0, 0.0);
double min = 0.0;
double max = 0.999;

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