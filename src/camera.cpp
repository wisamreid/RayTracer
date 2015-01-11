#include "camera.h"

using namespace stl;

Camera::Camera(int w_, int h_) : eye(0,0,1), ll(-1,-1,0), lr(1,-1,0), ul(-1,1,0), ur(1,1,0), h(h_), w(w_), objToWorld() {}
Camera::Camera(Point& eye_, Point& ll_, Point& lr_, Point& ul_, Point& ur_, int w_, int h_) : eye(eye_), ll(ll_), lr(lr_), ul(ul_), ur(ur_), h(h_), w(w_), objToWorld() {}
void Camera::setTransform(const Transform& t_) {objToWorld=t_;}
void Camera::setShape(int w_, int h_) {h=h_; w=w_;}

void Camera::generateRay(const Sample& s, Ray& r) {
  r.setStart(eye);
  double xWeight = s.getX()/w;
  double yWeight = s.getY()/h;
  Point p = (lr*xWeight + ll*(1-xWeight))*yWeight + (ur*xWeight + ul*(1-xWeight))*(1-yWeight);
  Vector d = objToWorld*(p-eye);
  d/=d.norm();
  r.setDirection(d);
}
