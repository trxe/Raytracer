#include <memory>
#include <vector>

#include "hittable.h"
#include "hittable_list.h"
#include "../utils/vec3.h"


/**
 * @brief HittableList 
 * 
 * @param r 
 * @param tmin 
 * @param tmax 
 * @param h 
 * @return true if the ray has hit_something
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