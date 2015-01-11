/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#ifndef NORMAL_H
#define NORMAL_H

#include "vector.h"

// stl :: String Theory Labs (Taking over a universe near you)
namespace stl
{

class Normal : public Vector {
 public:
  // constructors
  Normal() : Vector(0.0) {}
  Normal(double c) : Vector(c) {(*this)/=this->norm();}
  Normal(double x, double y, double z) : Vector(x,y,z) {(*this)/=this->norm();}
  Normal(Eigen::Vector3d v) : Vector(v) {(*this)/=this->norm();}

};

}

#endif
