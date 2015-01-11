#include "color.h"
#include <algorithm>
#include <cmath>

using namespace stl;

//Color class
Color::Color(): r(0.0), g(0.0), b(0.0) {}
Color::Color(double m): r(m), g(m), b(m) {}
Color::Color(double r_, double g_, double b_): r(r_), g(g_), b(b_) {}

const double Color::getR() const {return r;}
const double Color::getG() const {return g;}
const double Color::getB() const {return b;}

Color Color::normalized() const {double d = std::max(std::max(r,g),b); return Color(r/d, g/d, b/d);}

Color Color::operator + (const Color& c2) const {return Color(r+c2.r, g+c2.g, b+c2.b);}
Color Color::operator - (const Color& c2) const {return Color(r-c2.r, g-c2.g, b-c2.b);}
Color Color::operator * (const Color& c2) const {return Color(r*c2.r, g*c2.g, b*c2.b);}
Color Color::operator * (double m) const {return Color(r*m, g*m, b*m);}
Color Color::operator / (double m) const {return Color(r/m, g/m, b/m);}

Color& Color::operator += (const Color& c2) { this->r += c2.r; this->g += c2.g; this->b += c2.b; return *this; }
Color& Color::operator /= (double m) { this->r /= m; this->g /= m; this->b /= m; return *this; }

bool Color::operator != (const Color& c2) const { return this->r != c2.r || this->g != c2.g || this->b != c2.b; }

void Color::stream_to(std::ostream& os) const {os<<"R:"<<r<<" G:"<<g<<" B:"<<b;}
