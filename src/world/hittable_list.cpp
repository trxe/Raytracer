#include <memory>
#include <vector>

#include "hittable.h"
#include "hittable_list.h"
#include "../utils/vec3.h"


/**
 * @brief Checks for view ray hit from all hittables in the list and fills HitRecord h.
 * 
 * @param r View ray
 * @param tmin Episilon
 * @param tmax Max intersection distance
 * @param h Output HitRecord
 * @return true if the ray has hit something
 * @return false otherwise
 */
bool HittableList::hit(const Ray& r, double tmin, double tmax, HitRecord& h) const {
    HitRecord temp_rec;
    bool hit_something = false;
    double tclosest = tmax;

    for (const auto& object : objects) {
        // the hit method from the pointer to the object
        if (object->hit(r, tmin, tclosest, temp_rec)) {
            hit_something = true;
            h = temp_rec;
            tclosest = temp_rec.t;
        }
    }

    return hit_something;
}

bool HittableList::shadowed(const Ray &shadow, double tmin, double tmax,
        const shared_ptr<Hittable> &hittable) const {
    HitRecord temp_rec;
    for (const auto& object : objects) {
        // ignore if the object is the hittable to be shadowed/lit.
        if (std::addressof(object) == std::addressof(hittable)) continue;
        if (object->hit(shadow, tmin, tmax, temp_rec))
            return true;
    }
    return false;
}