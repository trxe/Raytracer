#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "rtweekend.h"

#include <iostream>

color red = color(0.8, 0.1, 0.5);
color blue = color(0.5, 0.7, 1.0);
color white = color(1.0, 1.0, 1.0);
color black = color(0.0, 0.0, 0.0);
double min = 0.0;
double max = 0.999;

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples
    double scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    out << static_cast<int>(clamp(r, min, max) * 256) << ' '
        << static_cast<int>(clamp(g, min, max) * 256) << ' '
        << static_cast<int>(clamp(b, min, max) * 256) << '\n';
}

#endif