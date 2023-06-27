#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <Eigen/Dense>

struct hit_record {
  Eigen::Vector3d point;
  Eigen::Vector3d normal;

  double t;
};


class Hittable {
  public:
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


#endif