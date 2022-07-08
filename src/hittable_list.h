#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include <memory>
#include <vector>

#include "vec3.h"
#include "hittable.h"

using std::shared_ptr;
using std::vector;

class HittableList : public Hittable {
public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object) {
    }

    void add(shared_ptr<Hittable> object) { objects.push_back(object); }
    void clear() { objects.clear(); }
    virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& h) const override;

public:
    vector<shared_ptr<Hittable>> objects;
};

#endif