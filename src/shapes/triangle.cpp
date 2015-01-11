/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#include "shapes/triangle.h"

// stl :: string theory labs (taking over a universe near you) 
using namespace stl;

#define DELTA 1e-6

Triangle::Triangle() : vertex(0), edge1(1,0,0), edge2(0,1,0) {}
Triangle::Triangle(Point& p1, Point& p2, Point& p3) : vertex(p1), edge1(p2-p1), edge2(p3-p1), hasNormals(false) {}
Triangle::Triangle(Point& p1, Point& p2, Point& p3, Normal& n1_, Normal& n2_, Normal& n3_) : vertex(p1), edge1(p2-p1), edge2(p3-p1), hasNormals(true), n1(n1_), n2(n2_), n3(n3_) {}
Triangle::Triangle(Point& p, Vector& e1, Vector& e2) : vertex(p), edge1(e1), edge2(e2) {}

bool Triangle::intersect(const Ray& ray, double*tHit, double* u, double* v) {
  // http://www.cs.virginia.edu/~gfx/Courses/2003/ImageSynthesis/papers/Acceleration/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
  Vector p = ray.getDirection().cross(edge2);
  double det = edge1.dot(p);

  if ( det < DELTA && det > -DELTA) {
    return false;
  }

  double invDet = 1.0/det;
  Vector tVec = ray.getStart()-vertex;
  *u = tVec.dot(p)*invDet;
  if (*u>1.0 || *u<0.0) {
    return false;
  }

  Vector q = tVec.cross(edge1);
  *v = ray.getDirection().dot(q)*invDet;
  if (*v+*u>1.0 || *v<0.0) {
    return false;
  }

  double t = edge2.dot(q)*invDet;
  if (t>ray.getTmax() || t<ray.getTmin()) {
    return false;
  }

  *tHit = t;
  return true;

}

bool Triangle::intersect(const Ray& ray) {
  double temp;
  double u;
  double v;
  return intersect(ray,&temp,&u,&v);
}

bool Triangle::intersect(const Ray& ray, double* tHit, LocalGeo* local) {
  double u;
  double v;
  if (intersect(ray,tHit,&u,&v)) {
    Point cp = ray.at(*tHit);
    local->setPosition(cp);
    if (hasNormals){
      local->setNormal(Normal(n1*(1.0-u-v)+n2*u+n3*v)); //TODO: Later
    } else {
      Normal temp = Normal(edge1.cross(edge2));
      if (ray.getDirection().dot(temp)<0.0){
        local->setNormal(Normal(edge1.cross(edge2)));
      } else {
        local->setNormal(Normal(edge2.cross(edge1)));
      }
    }
    return true;
  }
  else {
    return false;
  }
}

AABB Triangle::getAABB() const {
  Point v2 = vertex+edge1;
  Point v3 = vertex+edge2;
  double minX = std::min(vertex[0],std::min(v2[0],v3[0]));
  double minY = std::min(vertex[1],std::min(v2[1],v3[1]));
  double minZ = std::min(vertex[2],std::min(v2[2],v3[2]));
  double maxX = std::max(vertex[0],std::max(v2[0],v3[0]));
  double maxY = std::max(vertex[1],std::max(v2[1],v3[1]));
  double maxZ = std::max(vertex[2],std::max(v2[2],v3[2]));
  return AABB(Vector(minX,minY,minZ),Vector(maxX,maxY,maxZ));
}
