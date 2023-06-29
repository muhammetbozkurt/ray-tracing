#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <Eigen/Dense>
#include <random>


// Usings

using color = Eigen::Vector3d; 
using point3 = Eigen::Vector3d; 
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
inline static Eigen::Vector3d random_vector() {
    return Eigen::Vector3d(random_double(), random_double(), random_double());
}

inline static Eigen::Vector3d random_vector(double min, double max) {
    return Eigen::Vector3d(random_double(min,max), random_double(min,max), random_double(min,max));
}


Eigen::Vector3d random_in_unit_sphere() {
    while (true) {
        auto p = random_vector(-1,1);
        if (std::pow(p.norm(), 2)  >= 1) continue;
        return p;
    }
}


Eigen::Vector3d random_unit_vector() {
    return random_in_unit_sphere().normalized();
}


// Common Headers

#include "ray.h"

#endif