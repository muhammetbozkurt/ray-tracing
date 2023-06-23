#include <iostream>
#include <eigen3/Eigen/Dense>
#include "color_utility.hpp"
#include "ray.h"

using color = Eigen::Vector3d; 
using point3 = Eigen::Vector3d; 

double hit_sphere(const point3& center, double radius, const Ray& ray){
  Eigen::Vector3d oc =  ray.origin() - center;
  auto a = ray.direction().dot(ray.direction());
  auto b = 2.0 * oc.dot(ray.direction());
  auto c = oc.dot(oc) - radius * radius;
  auto discriminant = b*b - 4*a*c;
  if (discriminant < 0) {
    return -1.0;
  } else {
    //first t value that intersects the sphere
    return (-b - sqrt(discriminant) ) / (2.0*a);
  }
}

color ray_color(const Ray& r){
  // This function linearly blends white and blue depending on the heighet ofthe y coordinate after normalizing the ray direction.
  // returns the background color
  auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        Eigen::Vector3d N = (r.at(t) - Eigen::Vector3d(0,0,-1)).normalized();
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
  Eigen::Vector3d unit_direction = r.direction().normalized();
  t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0,1.0,1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
  // ppm image size
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);


  // camera

  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;

  auto origin = point3(0.0,0.0,0.0);
  auto horizontal = Eigen::Vector3d(viewport_width, 0, 0);
  auto vertical = Eigen::Vector3d(0, viewport_height, 0);
  point3 lower_left_corner = origin - horizontal/2 - vertical/2 - Eigen::Vector3d(0,0,focal_length);

  //render image

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j =  image_height-1 ; j >= 0; --j)
  {
    // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i < image_width; ++i)
    {
      auto u = double(i) / (image_width-1);
      auto v = double(j) / (image_height-1);
      Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
      color color = ray_color(r);
      write_color(std::cout, color);
    }
  }
  std::cerr << "\nDone.\n";

  return 0;
}
