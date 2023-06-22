#ifndef RAY_H
#define RAY_H


#include <eigen3/Eigen/Dense>

class Ray{
  public:
    Eigen::Vector3d orig;
    Eigen::Vector3d dir;


    Ray(){}
    Ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction)
      : orig(origin), dir(direction)
    {}

    Eigen::Vector3d origin() const {return orig;}
    Eigen::Vector3d direction() const {return dir;}

    Eigen::Vector3d at(double t) const{
      return orig + t*dir;
    }
};


#endif