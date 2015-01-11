/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shapes/shape.h"

// stl :: String Theory Labs (taking over a universe near you) 
namespace stl
{

class Circle : public Shape {
 private:
  Point center;
  double radius;

  bool intersect(const Ray& ray, double* tHit);

 public:
  // constructors
  Circle();
  Circle(Point& c_, double r_);

  bool intersect(const Ray& ray);
  bool intersect(const Ray& ray, double* tHit, LocalGeo* local);
  AABB getAABB() const;

};

}

#endif
