#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "aggprimitive.h"
#include "light.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class RayTracer {
 private:
  AggPrimitive allObjs;
  std::vector<Light*> lights;
  int maxDepth;
 public:
  RayTracer();
  RayTracer(AggPrimitive& allObjs, std::vector<Light*>& lights, int maxDepth);
  void trace(Ray& ray, Color& color, int depth);
  void createReflectedRay(const LocalGeo& localGeo, const Ray& ray, Ray& newRay);
  void createRefractedRay(const LocalGeo& localGeo, const Ray& ray, Ray& newRay, double n);
};

}

#endif
