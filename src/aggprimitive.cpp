#include "aggprimitive.h"
#include <limits>

using namespace stl;

AggPrimitive::AggPrimitive() : objs(0) {}
AggPrimitive::AggPrimitive(std::vector<Primitive*> objs_, std::string n) : objs(objs_), objs2(objs_), name(n) {}

bool AggPrimitive::intersect(const Ray& ray) {
  //std::cout << std::endl;
  return objs2.intersect(ray);

  // for (size_t i=0; i < objs.size(); i++) {
  //   if (objs[i]->intersect(ray)) {
  //     return true;
  //   }
  // }
  // return false;
}

bool AggPrimitive::intersect(const Ray& ray, double* tHit, Intersection* in) {
  //std::cout << std::endl;
  return objs2.intersect(ray,tHit,in);

  // double tempThit;
  // Intersection tempIn;

  // Primitive* minHitObj = NULL;
  // double minThit = std::numeric_limits<double>::infinity();
  // LocalGeo minLocalGeo;

  // for (size_t i=0; i < objs.size(); i++) {
  //   if (objs[i]->intersect(ray,&tempThit,&tempIn)) {
  //     if (tempThit < minThit) {
  //       minThit = tempThit;
  //       minHitObj = tempIn.getPrimitive();
  //       minLocalGeo = tempIn.getLocalGeo();
  //     }
  //   }
  // }

  // if (minHitObj != NULL) {
  //   *tHit = minThit;
  //   in->setPrimitive(minHitObj);
  //   in->setLocalGeo(minLocalGeo);
  //   return true;
  // }

  // return false;
}

const BRDF& AggPrimitive::getBRDF(const LocalGeo& l) const {
  // This should never get called, because in->primitive will
  // never be an aggregate primitive
  exit(-1);
}

const AABB& AggPrimitive::getAABB() {
  return objs2.getAABB();
}

void AggPrimitive::stream_to(std::ostream& os) const {os<<name;}
