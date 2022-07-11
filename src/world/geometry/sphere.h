#ifndef SPHERE_H
#define SPHERE_H

#include "../../utils/vec3.h"
#include "../../camera/ray.h"
#include "../../world/hittable.h"

class Sphere : public Hittable {
public: 
    Sphere() {}
    Sphere(Point3 cen, double r, shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m) {};

    virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& h) const override {
        vec3 oc = r.origin() - center;
        double a = dot(r.direction(), r.direction());
        double half_b = dot(r.direction(), oc);
        double c = dot(oc, oc) - radius * radius;
        // we are trying to see if there are 2, 1, or 0 solutions to
        // bb * t^2 + boc * t + ococ = 0
        double discriminant =  half_b * half_b - a * c;
        if (discriminant < 0) return false;
        double root1 = (-half_b - std::sqrt(discriminant)) / a;
            
        if (tmin > root1 || root1 > tmax) {
            root1 = (-half_b + std::sqrt(discriminant)) / a;
            if (tmin > root1 || root1 > tmax) return false;
        }
        
        h.t = root1;
        h.p = r.at(h.t);
        vec3 outward_normal = (h.p - center) / radius;
        h.set_face_normal(r, outward_normal);
        h.mat_ptr = mat_ptr;
        return true;
    }

public:
    Point3 center;
    double radius;
    shared_ptr<Material> mat_ptr;
};

#endif