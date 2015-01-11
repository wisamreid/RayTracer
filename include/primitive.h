#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "ray.h"
#include "intersection.h"
#include "brdf.h"
#include "localgeo.h"
#include "bvh/aabb.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class Primitive {
 public:
  virtual bool intersect(const Ray& ray) = 0;
  virtual bool intersect(const Ray& ray, double* tHit, Intersection* in) = 0;
  virtual const BRDF& getBRDF(const LocalGeo& l) const = 0;
  virtual const AABB& getAABB() = 0;
  virtual void stream_to(std::ostream& os) const = 0;
};

static inline std::ostream& operator << (std::ostream& os, const Primitive& p) {p.stream_to(os); return os;}

}

#endif
