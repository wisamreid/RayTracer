#include "light.h"
#include "vector.h"

using namespace stl;

//Light class
Light::Light(Color i_): i(i_), objToWorld() {}
void Light::setTransform(const Transform& t) {objToWorld=t;}
bool Light::isAmbient() {return false;}
bool Light::isPoint() {return false;}
bool Light::isArea() {return false;}
const FallOfType& Light::getFallOfType() const {return NONE;}

//PointLight class
PointLight::PointLight(Point pos_, Color i_, FallOfType fot_): Light(i_), pos(pos_), fot(fot_) {}
bool PointLight::isPoint() {return true;}
void PointLight::generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const {
  lcolor = i;
  Point pointInObjFrame = objToWorld.inverse()*local.getPosition(); // Object fram
  Vector dir = objToWorld*(pos-pointInObjFrame); // World frame
  double tMax = dir.norm();
  dir/=tMax;
  lray = Ray(local.getPosition(),dir,EPSILON,tMax); // World frame
}
void PointLight::stream_to(std::ostream& os) const {os<<"pLight("<<pos<<": "<<i<<")";}
void PointLight::setPosition(Point& pos_) {pos=pos_;}
const FallOfType& PointLight::getFallOfType() const {return fot;}

//DirectionLight class
DirectionLight::DirectionLight(Vector dir_, Color i_): Light(i_), dir(dir_) {}
void DirectionLight::generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const {
  lcolor = i;
  Vector temp = objToWorld*dir; // World frame
  temp/=-temp.norm(); //Flip direction to point from object to light
  lray = Ray(local.getPosition(),temp,EPSILON); // World frame
}
void DirectionLight::stream_to(std::ostream& os) const {os<<"dLight("<<dir<<": "<<i<<")";}
void DirectionLight::setDirection(Vector& dir_) {dir=dir_;}

//AmbientLight class
AmbientLight::AmbientLight(Color i_): Light(i_) {}
bool AmbientLight::isAmbient() {return true;}
void AmbientLight::generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const {
  lcolor = i;
  Vector dir = Vector(0.0);
  lray = Ray(local.getPosition(),dir,0.0,0.0);
}
void AmbientLight::stream_to(std::ostream& os) const {os<<"ambLight("<<i<<")";}

//AreaLight class
AreaLight::AreaLight(Point pos_, Color i_, FallOfType fot_, double r_, int numLights_) : PointLight(pos_, i_, fot_), radius(r_), numLights(numLights_) {}
bool AreaLight::isPoint() {return false;}
bool AreaLight::isArea() {return true;}
void AreaLight::generateLightRay(const LocalGeo& local, Ray& lray, Color& lcolor) const {
  // lcolor = i;
  // Point pointInObjFrame = objToWorld.inverse()*local.getPosition(); // Object fram
  // Vector dir = objToWorld*(pos-pointInObjFrame); // World frame
  // double tMax = dir.norm();
  // dir/=tMax;
  // lray = Ray(local.getPosition(),dir,EPSILON,tMax); // World frame
}
void AreaLight::stream_to(std::ostream& os) const {os<<"areaLight("<<pos<<": "<<i<< ", radius: "<< radius<<")";}