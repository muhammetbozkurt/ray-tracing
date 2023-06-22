#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <eigen3/Eigen/Dense>


void write_color(std::ostream &out ,Eigen::Vector3d color){
  out << static_cast<int>(255.999 * color[0]) << ' '
      << static_cast<int>(255.999 * color[1]) << ' '
      << static_cast<int>(255.999 * color[2]) << '\n'
}

#endif