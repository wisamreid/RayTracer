/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <Eigen/Core>

// stl :: String Theory Labs (Taking over a universe near you)
namespace stl
{

//class Point; // Forward declaration

class Vector : public Eigen::Vector3d {
 public:
  // constructors
  Vector(double c) : Eigen::Vector3d(c,c,c) {}
  Vector(double x, double y, double z) : Eigen::Vector3d(x,y,z) {}
  Vector(Eigen::Vector3d v) : Eigen::Vector3d(v) {}

  // +/- Vector with Point
  //inline Point operator + (const Point& p) { return Point(0.0); /*(Point)( Eigen::Vector3d::operator+(p.getBase()) );*/ }; // Casting to Point creates new object which is inefficient
  //inline Point operator - (const Point& p) { return (Point)( *(Eigen::Vector3d*)this - p ); };

  inline void stream_to(std::ostream& os) const {os<<"<"<< (*this)[0] << ", " << (*this)[1] << ", " << (*this)[2] <<">";};
  //std::cout << std::fixed << std::setw( 11 ) << std::setprecision( 6 ) << std::setfill( '0' ) << my_double;
};

static inline std::ostream& operator << (std::ostream& os, const Vector& v) {v.stream_to(os); return os;}

}

#endif
