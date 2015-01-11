#ifndef POINT_H
#define POINT_H

#include <Eigen/Core>
#include "vector.h"

// stl :: String Theory Labs (Taking over a universe near you)
namespace stl
{

class Transform; // Forward declaration
class PointLight;

class Point : private Eigen::Vector3d {
 friend class Transform;
 friend class Vector;
 friend class PointLight;
 private:
  inline const Eigen::Vector3d& getBase() const {return *this;};
 public:
  // constructors
  Point(double c) : Eigen::Vector3d(c,c,c) {}
  Point(double x, double y, double z) : Eigen::Vector3d(x,y,z) {}
  Point(Eigen::Vector3d p) : Eigen::Vector3d(p) {}

  inline double operator [] (size_t i) const {return (*this).getBase()[i];};

  // Subtract points to create a Vector
  inline Vector operator - (const Point& p) const { return (Vector)( *(Eigen::Vector3d*)this - p ); }; // Casting to Vector creates new object which is inefficient

  // +/- Point with Vector
  inline Point operator + (const Eigen::Vector3d& v) const { return (Point)( *(Eigen::Vector3d*)this + v ); }; // Casting to Point creates new object which is inefficient
  inline Point operator - (const Eigen::Vector3d& v) const { return (Point)( *(Eigen::Vector3d*)this - v ); };
  
  inline Point& operator += (const Eigen::Vector3d& v) { Eigen::Vector3d::operator+=(v); return *this; };
  inline Point& operator -= (const Eigen::Vector3d& v) { Eigen::Vector3d::operator-=(v); return *this; };

  inline Point operator + (const Point& p) const { return (Point)( *(Eigen::Vector3d*)this + p ); }; // Casting to Point creates new object which is inefficient
  inline Point operator * (const double c) const { return (Point)( *(Eigen::Vector3d*)this * c ); }; // Casting to Point creates new object which is inefficient

  inline void stream_to(std::ostream& os) const {os<<"("<< (*this).getBase()[0] << ", " << (*this).getBase()[1] << ", " << (*this).getBase()[2] <<")";};
  //std::cout << std::fixed << std::setw( 11 ) << std::setprecision( 6 ) << std::setfill( '0' ) << my_double;
};

static inline std::ostream& operator << (std::ostream& os, const Point& p) {p.stream_to(os); return os;}

}

#endif