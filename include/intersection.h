#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "localgeo.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class Primitive; //Forward declaration

class Intersection {
 private:
  Primitive* p;
  LocalGeo l;
 public:
  Intersection() {}
  Intersection(Primitive* p_, LocalGeo& l_) :  p(p_), l(l_) {}
  inline Primitive* getPrimitive() const {return p;};
  inline const LocalGeo& getLocalGeo() const {return l;};
  inline void setPrimitive(Primitive* p_) {p=p_;};
  inline void setLocalGeo(LocalGeo& l_) {l=l_;};
};

}

#endif
