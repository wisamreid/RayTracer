#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include "vector.h"
#include "transform.h"
#include "sample.h"
#include "ray.h"

// stl :: string theory labs (taking over a universe near you) 
namespace stl
{

class Camera {
 private:
  Point eye;
  Point ll;
  Point lr;
  Point ul;
  Point ur;
  int h, w;
  Transform objToWorld;
 public:
  Camera(int w_, int h_);
  Camera(Point& eye_, Point& ll_, Point& lr_, Point& ul_, Point& ur_, int w_, int h_);
  void setTransform(const Transform& t_);
  void setShape(int w, int h);
  void generateRay(const Sample& s, Ray& r);
};

}

#endif
