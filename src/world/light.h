#ifndef LIGHT_H
#define LIGHT_H
#include "hittable_list.h"
#include "../camera/ray.h"
#include "../utils/color.h"
#include <memory>

/**
 * @brief Superclass for all light sources.
 * 
 */
class Light {
public:
    /**
     * @brief Returns the luminance of this light source.
     * 
     * @param world HittableList of all hittable objects view world
     * @param object Object hit by view ray, being lit
     * @param rec Record of hit by view ray
     * @param tmin Epsilon
     * @param tmax Maximum intersection length
     * @return Color 
     */
    virtual Color lit(const HittableList& world, shared_ptr<Hittable> const &object,
        const HitRecord& rec, double tmin, double tmax) const = 0;

    vec3 pos;
};

class PointLight: public Light {
public:
    PointLight(const vec3& p, const Color& c) : pos(p), color(c) {}
    
    virtual Color lit(const HittableList &world, const shared_ptr<Hittable> &object,
        const HitRecord &rec, double tmin, double tmax
    ) const override {
        Ray shadow(pos, pos - rec.p);
        bool shadowed = world.shadowed(shadow, tmin, tmax, object);
        if (shadowed) return BLACK;
        return color;
    }
    vec3 pos;

private:
    Color color;
};

#endif