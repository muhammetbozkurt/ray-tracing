#include <iostream>
#include <eigen3/Eigen/Dense>
#include "color_utility.hpp"


int main()
{
  // ppm image size

  const int image_width = 256;
  const int image_height = 256;

  //render image

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j =  image_height-1 ; j >= 0; --j)
  {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i < image_width; ++i)
    {
      auto r = double(i) / (image_width-1);
      auto g = double(j) / (image_height-1);
      auto b = 0.25;

      Eigen::Vector3d color(r,g,b);

      write_color(std::cout, color);

    }
  }
  std::cerr << "\nDone.\n";

  return 0;
}
