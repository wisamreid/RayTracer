#ifndef OBJPRIMITIVE_H
#define OBJPRIMITIVE_H

#include "primitive.h"
#include <vector>
#include "bvh/staticaabbtree.h"
#include "transform.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class ObjPrimitive : public Primitive {
 private:
  StaticAABBTree faces;
  std::vector<Primitive*> faces2;
  Transform objToWorld;
  std::string name;
  AABB aabb;
  bool validAABB;
 public:
  ObjPrimitive();
  ObjPrimitive(std::vector<Primitive*> faces_, Transform& o2w, std::string n);
  bool intersect(const Ray& ray);
  bool intersect(const Ray& ray, double* tHit, Intersection* in);
  const BRDF& getBRDF(const LocalGeo& l) const;
  const AABB& getAABB();
  void stream_to(std::ostream& os) const;
};

static inline std::ostream& operator << (std::ostream& os, const ObjPrimitive& a) {a.stream_to(os); return os;}

}

#endif
