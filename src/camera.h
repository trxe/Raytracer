#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"
#include "rtweekend.h"

class camera {
public: 
    camera() {
        auto aspect_ratio = 16.0 / 9.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * aspect_ratio;
        auto focal_length = 1.0;

        origin = Point3(0.0, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        lower_left_corner = origin - 0.5 * vertical - 0.5 * horizontal - vec3(0.0, 0.0, focal_length);
    }

    Ray get_ray(double u, double v) const {
        return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

private:
        Point3 origin;
        vec3 vertical;
        vec3 horizontal;
        vec3 lower_left_corner;
};

#endif