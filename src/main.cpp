#include "scene.h"
#include "point.h"
#include "vector.h"
#include "normal.h"
#include "transform.h"

#include <iostream>
#include <Eigen/Core>

using namespace stl;

int main(int argc, const char* argv[]) {
  Scene scene = Scene();
  scene.loadSCN("test.scn");
  //scene.loadOBJ("test.obj");

  // Transform3d t;
  // t.setIdentity();
  // // t = Eigen::AngleAxisd(3.14/2,Vector(0,0,1))*Eigen::Scaling(Vector(1,2,3));
  // // Transform transform = (Transform)t;
  // // transform = transform*t;
  // Point p1 = Point(1,0,0);
  // Point p2 = Point(0,1,0);
  // Point p3 = Point(0,0,1);
  // std::cout << t*(p1-p2) << std::endl;
  // // std::cout << t*p2 << std::endl;
  // // std::cout << t*p3 << std::endl;


  // Vector v1 = Vector(0.5,0,0);
  // Vector v2 = Vector(1,1,0);
  // Vector v3 = v1.cross(v2);
  // double s1 = v1.dot(v2);
  // std::cout << v1 << std::endl;
  // std::cout << v2 << std::endl;
  // std::cout << v3 << std::endl;
  // std::cout << s1 << std::endl;
  // Point p4 = Point(-1,4,8)-Vector(0.0);
  // std::cout << p4 << std::endl;

  std::cout << "Press Enter/Return to begin rendering!" << std::endl;
  std::cin.get();
  std::cout << "In progress..." << std::endl;
  scene.render();
  std::cout << "Done!" << std::endl;

  Vector(0).cross(Vector(0)); //Main doesn't compile with eigen if this line is commented out...

  return 0;
}