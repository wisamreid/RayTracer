/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#ifndef SHAPE_H
#define SHAPE_H

#include "ray.h"
#include "localgeo.h"
#include "bvh/aabb.h"

// stl :: String Theory Labs (Taking over a universe near you) 
namespace stl
{

class Shape {
 public:
  virtual bool intersect(const Ray& ray) = 0;
  virtual bool intersect(const Ray& ray, double* tHit, LocalGeo* local) = 0;
  virtual AABB getAABB() const = 0;
};

}

#endif
