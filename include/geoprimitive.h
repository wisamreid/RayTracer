#ifndef GEOPRIMITIVE_H
#define GEOPRIMITIVE_H

#include "primitive.h"
#include "shapes/shape.h"
#include "material.h"
#include "transform.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class GeoPrimitive : public Primitive {
 private:
  Shape* shape;
  Material* material;
  bool hasTransform;
  Transform objToWorld;
  std::string name;
  AABB aabb;
  bool validAABB;
 public:
  GeoPrimitive(Shape* s, Material* m, std::string n);
  GeoPrimitive(Shape* s, Material* m, Transform& o2w, std::string n);
  bool intersect(const Ray& ray);
  bool intersect(const Ray& ray, double* tHit, Intersection* in);
  const BRDF& getBRDF(const LocalGeo& l) const;
  const AABB& getAABB();
  void stream_to(std::ostream& os) const;
};

static inline std::ostream& operator << (std::ostream& os, const GeoPrimitive& g) {g.stream_to(os); return os;}

}

#endif
