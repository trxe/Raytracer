#ifndef MATERIAL_H
#define MATERIAL_H

#include "../camera/ray.h"
#include "../utils/vec3.h"
#include "../utils/rtweekend.h"
#include "hittable.h"

/**
 * @brief Superclass of all materials.
 * 
 */
class Material {
public:
    /**
     * @brief Defines the direction of scattered light ray when hit.
     * 
     * @param r_in Incident ray
     * @param rec HitRecord containing hit normal info etc.
     * @param attenuation output, color
     * @param scattered output, outgoing ray
     * @return true if scattered ray is valid
     * @return false otherwise
     */
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
    Lambertian(const Color& a) : albedo(a) {}

    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) 
            scatter_direction = rec.normal;
        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    Color albedo;
};

class Metal : public Material {
public:
    Metal(const Color& a) : albedo(a) {}

    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const override {
        auto reflection = rec.normal + reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflection);
        attenuation = albedo;
        return dot(reflection, rec.normal) > 0;
    }

public:
    Color albedo;
};

class Dielectric : public Material {
public: 
    Dielectric(const double& refraction_index) : ir(refraction_index) {}

    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        bool not_refracting = refraction_ratio * sin_theta > 1.0;

        vec3 direction;
        if (not_refracting || schlick(cos_theta, 1.0, ir) > random_double()) {
            direction = reflect(unit_direction, rec.normal);
        } else {
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        }

        scattered = Ray(rec.p, direction);
        return true;
    }

public:
    double ir; // Index of Refraction

};

#endif