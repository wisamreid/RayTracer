#ifndef AABB_H
#define AABB_H

#include <vector>
#include <cmath>
#include "vector.h"
#include "ray.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class AABB {
 private:
  Vector min;
  Vector max;
 public:
  AABB() : min(0), max(0) {}
  AABB(Vector min_, Vector max_) : min(min_), max(max_) {}

  inline AABB merge(const AABB& aabb) {return AABB(Vector(std::min(min[0],aabb.min[0]),std::min(min[1],aabb.min[1]),std::min(min[2],aabb.min[2])),Vector(std::max(max[0],aabb.max[0]),std::max(max[1],aabb.max[1]),std::max(max[2],aabb.max[2])));}
  inline bool contains(const AABB& aabb) {return !(min[0]>aabb.min[0] || min[1]>aabb.min[1] || min[2]>aabb.min[2] || max[0]<aabb.max[0] || max[1]<aabb.max[1] || max[2]<aabb.max[2]);}
  inline double volume() {return (max[0]-min[0])*(max[1]-min[1])*(max[2]-min[2]);}
  inline void setMin(Vector& min_) {min=min_;}
  inline void setMax(Vector& max_) {max=max_;}
  inline const Vector& getMin() const {return min;}
  inline const Vector& getMax() const {return max;}

  inline bool intersect(const Ray& ray){
    double t0 = (min[0]-ray.getStart()[0])/ray.getDirection()[0];
    double t1 = (max[0]-ray.getStart()[0])/ray.getDirection()[0];
    double t2 = (min[1]-ray.getStart()[1])/ray.getDirection()[1];
    double t3 = (max[1]-ray.getStart()[1])/ray.getDirection()[1];
    double t4 = (min[2]-ray.getStart()[2])/ray.getDirection()[2];
    double t5 = (max[2]-ray.getStart()[2])/ray.getDirection()[2];

    double tMax = std::min(std::min(std::max(t0, t1), std::max(t2, t3)), std::max(t4, t5));
    double tMin = std::max(std::max(std::min(t0, t1), std::min(t2, t3)), std::min(t4, t5));

    if (tMax < 0 || tMax < tMin) {
        return false;
    } else {
      return true;
    }
  };

};

}

#endif
