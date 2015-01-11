#include "objprimitive.h"

using namespace stl;

ObjPrimitive::ObjPrimitive() : faces() {}
ObjPrimitive::ObjPrimitive(std::vector<Primitive*> faces_, Transform& o2w, std::string n) : faces(faces_), faces2(faces_), objToWorld(o2w), name(n), validAABB(false) {}

bool ObjPrimitive::intersect(const Ray& ray) {
  Ray objRay = (Transform)(objToWorld.inverse())*ray;
  return faces.intersect(objRay);

  // for (size_t i=0; i < faces2.size(); i++) {
  //   if (faces2[i]->intersect(ray)) {
  //     return true;
  //   }
  // }
  // return false;

}

bool ObjPrimitive::intersect(const Ray& ray, double* tHit, Intersection* in) {
  Ray objRay = (Transform)(objToWorld.inverse())*ray;
  if (!faces.intersect(ray,tHit,in)) {
    return false;
  }

  LocalGeo temp = objToWorld*in->getLocalGeo();
  in->setLocalGeo(temp);
  *tHit *= ray.getDirection().norm();

  return true;

  // double tempThit;
  // Intersection tempIn;

  // Primitive* minHitObj = NULL;
  // double minThit = std::numeric_limits<double>::infinity();
  // LocalGeo minLocalGeo;

  // for (size_t i=0; i < faces2.size(); i++) {
  //   if (faces2[i]->intersect(ray,&tempThit,&tempIn)) {
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

const BRDF& ObjPrimitive::getBRDF(const LocalGeo& l) const {
  // This should never get called, because intersection->primitive will
  // never be an obj primitive
  exit(-1);
}

const AABB& ObjPrimitive::getAABB() {
  if (!validAABB) {
    aabb = faces.getAABB();
    Vector center = (Vector)((aabb.getMax()+aabb.getMin())/2.0);
    Vector extents = (Vector)((aabb.getMax()-aabb.getMin())/2.0);
    Point p1 = objToWorld*(Point)(center + extents);
    Point p2 = objToWorld*(Point)(center + Vector(extents[0],extents[1],-extents[2]));
    Point p3 = objToWorld*(Point)(center + Vector(extents[0],-extents[1],extents[2]));
    Point p4 = objToWorld*(Point)(center + Vector(extents[0],-extents[1],-extents[2]));
    Point p5 = objToWorld*(Point)(center + Vector(-extents[0],extents[1],extents[2]));
    Point p6 = objToWorld*(Point)(center + Vector(-extents[0],extents[1],-extents[2]));
    Point p7 = objToWorld*(Point)(center + Vector(-extents[0],-extents[1],extents[2]));
    Point p8 = objToWorld*(Point)(center - extents);
    double minX = std::min(p1[0],std::min(p2[0],std::min(p3[0],std::min(p4[0],std::min(p5[0],std::min(p6[0],std::min(p7[0],p8[0])))))));
    double minY = std::min(p1[1],std::min(p2[1],std::min(p3[1],std::min(p4[1],std::min(p5[1],std::min(p6[1],std::min(p7[1],p8[1])))))));
    double minZ = std::min(p1[2],std::min(p2[2],std::min(p3[2],std::min(p4[2],std::min(p5[2],std::min(p6[2],std::min(p7[2],p8[2])))))));
    double maxX = std::max(p1[0],std::max(p2[0],std::max(p3[0],std::max(p4[0],std::max(p5[0],std::max(p6[0],std::max(p7[0],p8[0])))))));
    double maxY = std::max(p1[1],std::max(p2[1],std::max(p3[1],std::max(p4[1],std::max(p5[1],std::max(p6[1],std::max(p7[1],p8[1])))))));
    double maxZ = std::max(p1[2],std::max(p2[2],std::max(p3[2],std::max(p4[2],std::max(p5[2],std::max(p6[2],std::max(p7[2],p8[2])))))));
    Vector min = Vector(minX,minY,minZ);
    Vector max = Vector(maxX,maxY,maxZ);
    aabb.setMin(min);
    aabb.setMax(max);
    validAABB = true;
  }
  return aabb;
}

void ObjPrimitive::stream_to(std::ostream& os) const {os<<name;}
