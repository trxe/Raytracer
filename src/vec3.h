#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "rtweekend.h"

using std::sqrt;
using std::fabs;

struct vec3 {
    vec3() : e{0,0,0} {};
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {};

    double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // operator overloading. operator<op>()
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        // vec3& is a reference/alias
        // returning a reference allows us to make changes to the instance's internal properties
        // aka pointer to that thing
        // type& obj is equivalent to type &obj
        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        inline bool near_zero() {
            const auto s = 1e-8;
            return fabs(e[0]) < s && fabs(e[1]) < s && fabs(e[2]) < s;
        }

    public:
        double e[3];
};

// Type aliases for vec3
using Point3 = vec3;   // 3D point
using Color = vec3;    // RGB color


inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 reflect(const vec3 &v, const vec3 &normal) {
    return v - 2 * normal * dot(v, normal);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// lazy hack
vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1.0, 1.0);
        if (p.length_squared() < 1.0) return p;
    }
}

// true Lambertian reflection
vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

// alt formulation
vec3 random_in_hemisphere(const vec3& normal) {
    vec3 r = random_in_unit_sphere();
    if (dot(r, normal) < 0.0) return -r;
    return r;
}

#endif