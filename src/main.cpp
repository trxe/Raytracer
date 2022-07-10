#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include <iostream>
#include <memory>
#include <limits>
#include "vec3.h"
#include "color.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "material.h"
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"

/**
 * @brief Computes the ray's color based on Whitted ray tracing with
 * 
 * @param r 
 * @param world 
 * @param depth 
 * @return Color of ray's pixel
 */
Color ray_color(const Ray& r, const Hittable& world, int depth) {
	HitRecord rec;
	if (depth <= 0) return BLACK;
	if (world.hit(r, 0.001, INFTY, rec)) {
		Color attenuation;
		Ray scattered;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth-1);
		return BLACK;
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0-t)*WHITE + t*BLUE;
}

/**
 * @brief Main entry point into Raytracer. 
 * Defines World objects, Image settings, and renders to png.
 * 
 * @param argc number of arguments
 * @param argv argv[1] is the output image filename, defaults to img/output.png if not present.
 * @return int 0 if no issues.
 */
int main(int argc, char **argv) {
	
	// World

	shared_ptr<Material> mat_ground = make_shared<Lambertian>(0.6 * YELLOW);
	shared_ptr<Material> mat_center = make_shared<Lambertian>(0.6 * RED);
	shared_ptr<Material> mat_left = make_shared<Metal>(0.8 * WHITE);
	shared_ptr<Material> mat_right = make_shared<Metal>(Color(0.8, 0.6, 0.2));

	HittableList world;
	world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5, mat_center));
	world.add(make_shared<Sphere>(Point3(-1.0, 0, -1), 0.5, mat_left));
	world.add(make_shared<Sphere>(Point3(1.0, 0, -1), 0.5, mat_right));
	world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100, mat_ground));

	// Image config

	double aspect_ratio = 16.0 / 9.0;
	int image_width = 640;
	int image_height = static_cast<int>(image_width / aspect_ratio);
	int channels = 4;
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// Camera

	Camera cam;

	// Render

	unsigned char *data = new unsigned char[channels * image_width * image_height];

	for (int row = image_height - 1; row >= 0; row--) {
		std::cerr << "\rLines remaining: " << row << ' ' << std::flush;
		for (int col = 0; col < image_width; col++) {
			Color pixel_color(0.0, 0.0, 0.0);
			for (int s = 0; s < samples_per_pixel; s++) {
				double u = (double(col) + random_double()) / (image_width - 1);
				double v = (double(row) + random_double()) / (image_height - 1);
				Ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			int *cols = getIntColor(pixel_color, samples_per_pixel);
			for (int c = 0; c < channels; c++) {
				int src_index = c + channels * col + channels * image_width * (image_height - row);
				int val = c == 3 ? 255 : cols[c];
				data[src_index] = (unsigned char)val;
			}
		}
	}

	const char *filename = argc > 1 ? argv[1] : "img/output.png";
	stbi_write_png(filename, image_width, image_height, channels, data, image_width * channels);
}