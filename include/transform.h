#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Geometry>
#include "vector.h"
#include "point.h"
#include "normal.h"
#include "ray.h"
#include "localgeo.h"

// stl :: String Theory Labs (Taking over a universe near you)
namespace stl
{

typedef Eigen::Transform<double,3,Eigen::Affine> Transform3d;

class Transform : public Transform3d{
 public:
  inline Transform() {this->setIdentity();};
  inline Transform(const Transform3d& t) : Transform3d(t) {};
  inline Vector operator * (const Vector& v) const {return (Vector)(this->linear()*v);};
  inline Point operator * (const Point& p) const {return Transform3d::operator*(p);};
  inline Normal operator * (const Normal& n) const {return Normal(this->linear().inverse().transpose()*n);};
  inline Ray operator * (const Ray& r) const {Point p = this->operator*(r.getStart()); Vector d = this->operator*(r.getDirection()); return Ray(p,d,r.getTmin(),r.getTmax());}
  inline LocalGeo operator * (const LocalGeo& l) const {Point p = this->operator*(l.getPosition()); Normal n = this->operator*(l.getNormal()); return LocalGeo(p,n);}
  inline Transform operator * (const Transform3d& t) const {return (Transform)Transform3d::operator*(t);}
};

}

#endif
