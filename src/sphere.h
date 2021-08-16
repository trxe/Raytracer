#ifndef SPHERE_H
#define SPHERE_H
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class sphere : public hittable {
    public: 
        sphere() {}
        sphere(point3 cen, double r) : center(cen), radius(r) {};

        virtual bool hit(const ray& r, double tmin, double tmax, hit_record& h) const override {
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
            return true;
        }

    public:
        point3 center;
        double radius;
};

/*
bool sphere::hit(const ray& r, double tmin, double tmax, hit_record& h) const {
	vec3 oc = r.origin() - center;
	double bb = dot(r.direction(), r.direction());
	double boc = dot(r.direction(), oc);
	double ococ = dot(oc, oc) - radius * radius;
	// we are trying to see if there are 2, 1, or 0 solutions to
	// bb * t^2 + boc * t + ococ = 0
	double discriminant =  boc * boc - bb * ococ;
	if (discriminant < 0) return false;
	double root1 = (-boc - std::sqrt(discriminant)) / bb;
    if (tmin < root1 && root1 < tmax) {
        h.t = root1;
        h.p = r.at(root1);
        vec3 outward_normal = (h.p - center) / radius;
        h.set_face_normal(r, outward_normal);
        return true;
    }
    return false;
}
*/
#endif