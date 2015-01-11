#ifndef LIGHT_H
#define LIGHT_H

#define EPSILON 1e-6

#include "transform.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "localgeo.h"
#include "ray.h"

// stl :: string theory labs (taking over a universe near you) 
namespace stl
{

enum FallOfType { NONE, LINEAR, QUADRATIC};

class Light {
 protected:
  Color i;
  Transform objToWorld;
 public:
  Light(Color i);
  void setTransform(const Transform& t);
  virtual bool isAmbient();
  virtual bool isPoint();
  virtual bool isArea();
  virtual void generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const = 0;
  virtual const FallOfType& getFallOfType() const;
  virtual void stream_to(std::ostream& os) const = 0;
};

class PointLight: public Light {
 protected:
  Point pos;
  FallOfType fot; // Fall Of Type
 public:
  PointLight(Point pos, Color i, FallOfType fot);
  bool isPoint();
  void generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const;
  void stream_to(std::ostream& os) const;
  void setPosition(Point& pos);
  const FallOfType& getFallOfType() const;
};

class DirectionLight: public Light {
 protected:
  Vector dir;
 public:
  DirectionLight(Vector dir, Color i);
  void generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const;
  void stream_to(std::ostream& os) const;
  void setDirection(Vector& dir);
};

class AmbientLight: public Light {
 public:
  AmbientLight(Color i);
  bool isAmbient();
  void generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const;
  void stream_to(std::ostream& os) const;
};

class AreaLight: public PointLight {
 protected:
  double radius;
  int numLights;
 public:
  AreaLight(Point pos, Color i, FallOfType fot, double radius, int numLights);
  bool isArea();
  bool isPoint();
  void generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const;
  void stream_to(std::ostream& os) const;
};

static inline std::ostream& operator << (std::ostream& os, const Light& l) {l.stream_to(os); return os;}

}

#endif
