#ifndef AGGPRIMITIVE_H
#define AGGPRIMITIVE_H

#include "primitive.h"
#include <vector>
#include "bvh/dynamicaabbtree.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class AggPrimitive : public Primitive {
 private:
  std::vector<Primitive*> objs;
  DynamicAABBTree objs2;
  std::string name;
 public:
  AggPrimitive();
  AggPrimitive(std::vector<Primitive*> objs_, std::string n);
  bool intersect(const Ray& ray);
  bool intersect(const Ray& ray, double* tHit, Intersection* in);
  const BRDF& getBRDF(const LocalGeo& l) const;
  const AABB& getAABB();
  void stream_to(std::ostream& os) const;
};

static inline std::ostream& operator << (std::ostream& os, const AggPrimitive& a) {a.stream_to(os); return os;}

}

#endif
