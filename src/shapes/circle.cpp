/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#include "shapes/circle.h"
#include "math.h"

// stl :: string theory labs (taking over a universe near you) 
using namespace stl;

Circle::Circle() : center(0.0), radius(1.0) {}
Circle::Circle(Point& c_, double r_) : center(c_), radius(r_) {}

bool Circle::intersect(const Ray& ray, double*tHit) {
  Vector d = ray.getDirection();
  Vector ec = ray.getStart()-center;
  double a = d.dot(d);
  double b = d.dot(ec)*2;
  double c = ec.dot(ec)-radius*radius;
  double discrim = b*b-4*a*c;

  if (discrim<0) {
    return false;
  }
  else if (discrim==0) {
    double t = -b/(2*a);
    if (t>=ray.getTmin() && t<=ray.getTmax()) {
      *tHit = t;
      return true;
    }
    else {
      return false;
    }
  }
  else {
    double sqrt_discrim = sqrt(discrim);
    double t1 = (-b+sqrt_discrim)/(2*a);
    double t2 = (-b-sqrt_discrim)/(2*a);
    if (t2 > t1) {
      // Make sure t1 >= t2
      double temp = t1;
      t1 = t2;
      t2 = temp;
    }

    if (t1<ray.getTmin() || t2>ray.getTmax()) {
      return false;
    }
    else if (t2>=ray.getTmin()) {
      *tHit = t2;
      return true;
    }
    else if (t1<=ray.getTmax()) {
      *tHit = t1;
      return true;
    }
    else {
      return false;
    }

  }
}

bool Circle::intersect(const Ray& ray) {
  double temp;
  return intersect(ray,&temp);
}

bool Circle::intersect(const Ray& ray, double* tHit, LocalGeo* local) {
  if (intersect(ray,tHit)) {
    Point cp = ray.at(*tHit);
    local->setPosition(cp);
    local->setNormal(Normal(cp-center));
    return true;
  }
  else {
    return false;
  }
}

AABB Circle::getAABB() const {
  return AABB(Vector(center-Point(radius)),Vector(center[0]+radius,center[1]+radius,center[2]+radius));
}
