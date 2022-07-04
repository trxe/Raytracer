#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "rtweekend.h"

class Material {
    public:
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

#endif