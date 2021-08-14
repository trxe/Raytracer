#include <iostream>
#include <memory>
#include <limits>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"

color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r,0, infinity, rec)) {
		return 0.5 * (rec.normal + white);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0-t)*white + t*blue;
}

int main() {
	
	//Image

	auto aspect_ratio = 16.0 / 9.0;
	auto image_width = 400;
	auto image_height = static_cast<int>(400 / aspect_ratio);

	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));

	// Camera

	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * aspect_ratio;
	auto vertical = vec3(0.0, viewport_height, 0.0);
	auto horizontal = vec3(viewport_width, 0.0, 0.0);
	auto focal_length = 1.0;

	vec3 origin = vec3(0.0, 0.0, 0.0);
	vec3 lower_left_corner = origin - 0.5 * vertical - 0.5 * horizontal - vec3(0.0, 0.0, focal_length);

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int row = image_height - 1; row >= 0; row--) {
		std::cerr << "\rLines remaining: " << row << ' ' << std::flush;
		for (int col = 0; col < image_width; col++) {
			auto u = double(col) / (image_width - 1);
			auto v = double(row) / (image_height - 1);
			ray r = ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			color pixel_color = ray_color(r, world);
			write_color(std::cout, pixel_color);
		}
	}

	std::cerr << "\nDone." << std::endl;
}