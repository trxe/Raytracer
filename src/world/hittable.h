#ifndef HITTABLE_H
#define HITTABLE_H
#include "../utils/vec3.h"
#include "../camera/ray.h"

class Material;

/**
 * @brief Record containing point p, normal, material, ray's t-value and 
 * whether the hit is a front-face.
 * 
 */
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

/**
 * @brief Superclass of all ray-hittable objects in scene.
 * 
 */
class Hittable {
public:
    /**
     * @brief Returns if the ray has hit the Hittable object within valid range of t.
     * 
     * @param r Incident ray
     * @param tmin Minimum epsilon tmin
     * @param tmax Maximum t_max 
     * @param h HitRecord to fill in
     * @return true If the ray has hit the object
     * @return false otherwise
     */
    virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& h) const = 0;
};

#endif