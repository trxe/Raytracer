#include <iostream>
#include <memory>
#include <limits>
#include "vec3.h"
#include "color.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"

color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;
	if (depth <= 0) return black;
	if (world.hit(r,0, inf, rec)) {
		// point3 target = rec.p + rec.normal + random_in_unit_sphere(); 
		return 0.5 * ray_color(ray(rec.p, - rec.p), world, depth-1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0-t)*white + t*blue;
}

int main() {
	
	// World

	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	//Image

	auto aspect_ratio = 16.0 / 9.0;
	auto image_width = 400;
	auto image_height = static_cast<int>(400 / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 20;

	// Camera

	camera cam;

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int row = image_height - 1; row >= 0; row--) {
		std::cerr << "\rLines remaining: " << row << ' ' << std::flush;
		for (int col = 0; col < image_width; col++) {
			color pixel_color(0.0, 0.0, 0.0);
			for (int s = 0; s < samples_per_pixel; s++) {
				auto u = (double(col) + random_double()) / (image_width - 1);
				auto v = (double(row) + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone." << std::endl;
}