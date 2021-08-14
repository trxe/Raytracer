#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

color red = color(0.8, 0.1, 0.5);
color white = color(1.0, 1.0, 1.0);
color blue = color(0.5, 0.7, 1.0);

void write_color(std::ostream &out, color pixel_color) {
    out << static_cast<int>(pixel_color.x() * 255.999) << ' '
        << static_cast<int>(pixel_color.y() * 255.999) << ' '
        << static_cast<int>(pixel_color.z() * 255.999) << '\n';
}

#endif