#ifndef HITTABLE_H
#define HITTABLE_H
#include "vec3.h"
#include "ray.h"

class Material;

struct HitRecord {
    Point3 p;
    vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray& r, const vec3& outward_normal) {
        // setting the normal to always be going against the ray.
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& h) const = 0;
};

#endif