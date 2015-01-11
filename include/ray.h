#ifndef RAY_H
#define RAY_H

#include <limits>
#include <iostream>
#include "vector.h"
#include "point.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class Ray {
 private:
  Point start;
  Vector dir;
  double tMin;
  double tMax;
 public:
  Ray() : start(0.0), dir(0.0), tMin(0.0), tMax(std::numeric_limits<double>::infinity()) {};
  Ray(const Point& p_, const Vector& d_) : start(p_), dir(d_), tMin(0.0), tMax(std::numeric_limits<double>::infinity()) {};
  Ray(const Point& p_, const Vector& d_, double tMin_) : start(p_), dir(d_), tMin(tMin_), tMax(std::numeric_limits<double>::infinity()) {};
  Ray(const Point& p_, const Vector& d_, double tMin_, double tMax_) : start(p_), dir(d_), tMin(tMin_), tMax(tMax_) {};
  inline const Point at(double t) const {return start+dir*t;};
  inline const Point& getStart() const {return start;};
  inline const Vector& getDirection() const {return dir;};
  inline const double getTmin() const {return tMin;};
  inline const double getTmax() const {return tMax;};
  inline void setStart(Point& s_) {start=s_;};
  inline void setDirection(Vector& d_) {dir=d_;};
  inline void setTmin(double tMin_) {tMin=tMin_;};
  inline void setTmax(double tMax_) {tMax=tMax_;};
  inline void normalize() {dir/=dir.norm();}
  inline void stream_to(std::ostream& os) const {os<< start <<", "<< dir << ": " << tMin << " to " << tMax;};
};

static inline std::ostream& operator << (std::ostream& os, const Ray& r) {r.stream_to(os); return os;}

}

#endif
