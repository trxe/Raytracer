#include <memory>
#include <vector>

#include "vec3.h"
#include "hittable.h"

using std::shared_ptr;
using std::make_shared;
using std::vector;

class hittable_list : public Hittable {
    public:
        hittable_list() {}
        hittable_list(shared_ptr<Hittable> object) {
        }

        void add(shared_ptr<Hittable> object) { objects.push_back(object); }
        void clear() { objects.clear(); }
        virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& h) const override;

    public:
        vector<shared_ptr<Hittable>> objects;
};

bool hittable_list::hit(const Ray& r, double tmin, double tmax, HitRecord& h) const {
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