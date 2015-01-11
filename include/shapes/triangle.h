/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shapes/shape.h"

// stl :: String Theory Labs (taking over a universe near you) 
namespace stl
{

class Triangle : public Shape {
 private:
  Point vertex;
  Vector edge1;
  Vector edge2;

  bool hasNormals;
  Normal n1;
  Normal n2;
  Normal n3;

  bool intersect(const Ray& ray, double* tHit, double* u, double* v);

 public:
  // constructors
  Triangle();
  Triangle(Point& p1, Point& p2, Point& p3);
  Triangle(Point& p1, Point& p2, Point& p3, Normal& n1_, Normal& n2_, Normal& n3_);
  Triangle(Point& p, Vector& e1, Vector& e2);

  bool intersect(const Ray& ray);
  bool intersect(const Ray& ray, double* tHit, LocalGeo* local);
  AABB getAABB() const;

};

}

#endif
