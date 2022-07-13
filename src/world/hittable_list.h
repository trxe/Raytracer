#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include "geometry/sphere.h"
#include "hittable.h"
#include "material.h"
#include "../utils/color.h"
#include "../utils/vec3.h"

using std::shared_ptr;
using std::vector;

/**
 * @brief List of hittables to go through to find the front-most.
 * 
 */
class HittableList {
public:
    void add(shared_ptr<Hittable> object) { objects.push_back(object); }
    void clear() { objects.clear(); }
    bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec, shared_ptr<Hittable> hitobj) const;
    bool shadowed(const Ray& shadow, double tmin, double tmax, shared_ptr<Hittable> const &hittable) const;

public:
    vector<shared_ptr<Hittable>> objects;
};

/**
 * @brief Definition for three ball objects
 * 
 * @return HittableList world
 */
inline HittableList threeBallsWorld() {
	shared_ptr<Material> mat_ground = make_shared<Lambertian>(0.5 * RED);
	shared_ptr<Material> mat_center = make_shared<Lambertian>(0.6 * BLUE + 0.1 * RED);
	shared_ptr<Material> mat_left = make_shared<Metal>(0.2 * YELLOW, YELLOW, WHITE, 16);
	shared_ptr<Material> mat_right = make_shared<Dielectric>(1.5);

	HittableList world;
	world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5, mat_center));
	world.add(make_shared<Sphere>(Point3(-1.0, 0, -1), 0.5, mat_left));
	world.add(make_shared<Sphere>(Point3(1.0, 0, -1), 0.5, mat_right));
	world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100, mat_ground));

    return world;
}

inline HittableList observeShadowWorld() {
	HittableList world;
    return world;
}

#endif