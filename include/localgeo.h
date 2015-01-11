#ifndef LOCALGEO_H
#define LOCALGEO_H

#include "point.h"
#include "normal.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class LocalGeo {
 private:
  Point p;
  Normal n;
  //TextureCoord t;
 public:
  LocalGeo() : p(0.0), n() {};
  LocalGeo(const Point& p_, const Normal& n_) : p(p_), n(n_) {};
  inline const Point& getPosition() const {return p;};
  inline const Normal& getNormal() const {return n;};
  inline void setPosition(const Point& p_) {p=p_;};
  inline void setNormal(const Normal& n_) {n=n_;};
};

}

#endif
