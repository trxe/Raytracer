#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "../utils/rtweekend.h"
#include "../utils/vec3.h"
#include <math.h>

class Camera {
public: 
    /**
     * @brief With default origin 0,0,0, direction 0,0,1, aspect_ratio 16:9 and focal length 1.0.
     * 
     * For Whitted ray tracing.
     * 
     */
    Camera() {
        auto aspect_ratio = 16.0 / 9.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * aspect_ratio;
        auto focal_length = 1.0;

        origin = Point3(0.0, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        lower_left_corner = origin - 0.5 * vertical - 0.5 * horizontal - vec3(0.0, 0.0, focal_length);
        lens_radius = 0.0;
    }

    /**
     * @brief With default origin 0,0,0 and direction 0,0,1.
     * 
     * For Whitted ray tracing.
     * 
     * @param vfov vertical field of view in radians.
     * @param focal_length distance from camera to lens
     * @param aspect_ratio height over width
     */
    Camera(double vfov, double focal_length, double aspect_ratio) {
        auto viewport_height = 2.0 * tan(vfov/2) * focal_length;
        auto viewport_width = viewport_height * aspect_ratio;

        origin = Point3(0.0, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        lower_left_corner = origin - 0.5 * vertical - 0.5 * horizontal - vec3(0.0, 0.0, focal_length);
        lens_radius = 0.0;
    }

    /**
     * @brief Camera defined with cameraLookAt vectors, fov, focal length and aspect ratio.
     * 
     * For distributed ray tracing.
     * 
     * @param eye position of eye
     * @param at position you are looking at
     * @param up upwards vector
     * @param vfov vertical field of view in radians.
     * @param aspect_ratio height over width
     * @param aperture diameter of lens for Distributed Ray Tracing
     */
    Camera(const vec3& eye, const vec3& at, const vec3& up, double vfov, 
            double aspect_ratio, double aperture) {
        auto focal_length = (eye - at).length();
        auto viewport_height = 2.0 * tan(vfov/2) * focal_length;
        auto viewport_width = viewport_height * aspect_ratio;
        auto direction = unit_vector(eye - at);
        origin = eye;
        horizontal = cross(unit_vector(up), direction);
        vertical = viewport_height * cross(direction, horizontal);
        horizontal *= viewport_width;

        lower_left_corner = origin - 0.5 * vertical - 0.5 * horizontal - direction * focal_length;
        lens_radius =  aperture / 2;
    }

    /**
     * @brief Get the ray from origin passing through a pixel at image coordinates u, v.
     * 
     * @param u x-coordinate, ranges from 0 to 1 (left-most to right-most).
     * @param v y-coordinate, ranges from 0 to 1 (bottom-most to top-most).
     * @return Ray from origin through pixel
     */
    Ray get_ray(double u, double v) const {
        // Whitted ray tracing
        if (lens_radius == 0.0) {
            return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

        vec3 offset = random_in_unit_disk() * lens_radius;
        offset[0] *= u;
        offset[1] *= v;

        // return 
        return Ray(origin + offset,
                    lower_left_corner + u*horizontal + v*vertical - origin - offset);
    }

private:
        Point3 origin;
        vec3 vertical;
        vec3 horizontal;
        vec3 lower_left_corner;
        double lens_radius;
};

#endif