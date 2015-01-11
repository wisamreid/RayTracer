#include "geoprimitive.h"

using namespace stl;

GeoPrimitive::GeoPrimitive(Shape* s, Material* m, std::string n) : shape(s), material(m), hasTransform(false), name(n), validAABB(false) {}
GeoPrimitive::GeoPrimitive(Shape* s, Material* m, Transform& o2w, std::string n) : shape(s), material(m), hasTransform(true), objToWorld(o2w), name(n), validAABB(false) {}

bool GeoPrimitive::intersect(const Ray& ray) {
  if (hasTransform) {
    Ray objRay = (Transform)(objToWorld.inverse())*ray;
    return shape->intersect(objRay);
  } else {
    return shape->intersect(ray);
  }
}

bool GeoPrimitive::intersect(const Ray& ray, double* tHit, Intersection* in) {
  if (hasTransform) {
    Ray objRay = (Transform)(objToWorld.inverse())*ray;
    LocalGeo l;

    if (!shape->intersect(objRay,tHit,&l)) {
      return false;
    }
    
    in->setPrimitive(this);
    l = objToWorld*l;
    in->setLocalGeo(l);
    *tHit *= ray.getDirection().norm();

    return true;
  } else {
    LocalGeo l;

    if (!shape->intersect(ray,tHit,&l)) {
      return false;
    }
    
    in->setPrimitive(this);
    in->setLocalGeo(l);

    return true;
  }

}

const BRDF& GeoPrimitive::getBRDF(const LocalGeo& l) const {
  return material->getBRDF(l);
}

const AABB& GeoPrimitive::getAABB() {
  if (!validAABB) {
    if (hasTransform){
      aabb = shape->getAABB();
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
    } else {
      aabb = shape->getAABB();
    }
    validAABB = true;
  }
  return aabb;
}

void GeoPrimitive::stream_to(std::ostream& os) const {os<<name;}