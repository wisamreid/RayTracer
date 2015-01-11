#ifndef SAMPLE_H
#define SAMPLE_H

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class Sample {
 private:
  double x, y;
 public:
  Sample(): x(0.0), y(0.0) {};
  Sample(double x_, double y_): x(x_), y(y_) {};
  inline void setX(double x_) {x=x_;};
  inline void setY(double y_) {y=y_;};
  inline double getX() const {return x;};
  inline double getY() const {return y;};
  //inline void stream_to(std::ostream& os) const {os << "[" << x << ", " << y << "]";};
};

//static inline std::ostream& operator << (std::ostream& os, const Sample& s) {s.stream_to(os); return os;}

}

#endif
