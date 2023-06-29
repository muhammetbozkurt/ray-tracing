#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "color_utility.hpp"

#include <iostream>
#include <cmath>
#include "camera.h"

double hit_sphere(const point3& center, double radius, const Ray& ray){
  Eigen::Vector3d oc =  ray.origin() - center;
  auto a = std::pow(ray.direction().norm(), 2);
  auto half_b = oc.dot(ray.direction());
  auto c = std::pow(oc.norm(), 2) - radius * radius;
  auto discriminant = half_b*half_b - a*c;
  if (discriminant < 0) {
    return -1.0;
  } else {
    //first t value that intersects the sphere
    return (-half_b - sqrt(discriminant) ) / a;
  }
}

color ray_color(const Ray& r, const Hittable& world, int depth) {
  hit_record rec;

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    return color(0,0,0);

  // if the ray hits the any sphere, light needs to lose its power/brightness (in our example 0.5)
  // and the ray needs to be reflected (recursive call)
  if (world.hit(r, 0.001, infinity, rec)) {
      point3 target = rec.point + rec.normal + random_unit_vector();
      return 0.5 * ray_color(Ray(rec.point, target - rec.point), world, depth-1);
  }
  Eigen::Vector3d unit_direction = r.direction().normalized();
  auto t = 0.5*(unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0,1.0,1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
  // ppm image size
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  // World
    Hittable_list world;
    world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));

  // camera
  Camera cam;

  //render image

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height-1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width-1);
        auto v = (j + random_double()) / (image_height-1);
        Ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";

  return 0;
}
