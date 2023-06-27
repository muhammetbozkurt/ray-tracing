#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include <Eigen/Dense>


class Sphere: public Hittable {
  public:
    Eigen::Vector3d center;
    double radius;

    Sphere() {}
    Sphere(Eigen::Vector3d cen, double r) : center(cen), radius(r) {};

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& record) const override;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& record) const{
  Eigen::Vector3d oc =  r.origin() - center;
  auto a = std::pow(r.direction().norm(), 2);
  auto half_b = oc.dot(r.direction());
  auto c = std::pow(oc.norm(), 2) - radius * radius;
  auto discriminant = half_b*half_b - a*c;
  if (discriminant < 0) 
    return false;
    
  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrt(discriminant) ) / a;
  if (root < t_min || t_max < root) {
    return false;
  }
  record.t = root;
  record.point = r.at(record.t);
  record.normal = (record.point - center) / radius;
  return true;
}



#endif