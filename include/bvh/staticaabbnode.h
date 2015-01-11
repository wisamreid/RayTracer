#ifndef STATICAABBNODE_H
#define STATICAABBNODE_H

#include "bvh/aabb.h"
#include "primitive.h"
#include <limits>

#define MAX_DEPTH 10

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class StaticAABBNode {
 public:
  StaticAABBNode* children[2];

  AABB aabb;
  std::vector<Primitive*> leafObjs; // Leaf nodes only

  StaticAABBNode() {children[0]=NULL;children[1]=NULL;};

  inline void buildTree(std::vector<Primitive*>& objs, int currDepth) {
    if (currDepth >= MAX_DEPTH){
      leafObjs = objs;
      return;
    }

    for (size_t i = 0; i<objs.size(); i++) {
      aabb = aabb.merge(objs[i]->getAABB());
    }

    //Get largest axis
    double range[3];
    range[0] = aabb.getMax()[0]-aabb.getMin()[0];
    range[1] = aabb.getMax()[1]-aabb.getMin()[1];
    range[2] = aabb.getMax()[2]-aabb.getMin()[2];


    std::vector<Primitive*> left;
    AABB leftaabb = aabb;
    std::vector<Primitive*> right;
    AABB rightaabb = aabb;
    int axis;
    if (range[0] > range[1] && range[0] > range[2]) {
      axis=0;
    } else if (range[1] > range[2] && range[1] > range[0]) {
      axis=1;
    } else {
      axis=2;
    }

    Vector extents = (Vector)((aabb.getMax()-aabb.getMin())/2.0);

    Vector temp = leftaabb.getMax();
    temp[axis] -= extents[axis];
    leftaabb.setMax(temp);

    temp = rightaabb.getMin();
    temp[axis] += extents[axis];
    rightaabb.setMin(temp);

    for (size_t i = 0; i<objs.size(); i++) {
      if (leftaabb.contains(objs[i]->getAABB())) {
        left.push_back(objs[i]);
      } else if (rightaabb.contains(objs[i]->getAABB())) {
        right.push_back(objs[i]);
      } else {
        left.push_back(objs[i]);
        right.push_back(objs[i]);
      }
    }

    children[0] = new StaticAABBNode();
    children[0]->buildTree(left, currDepth+1);
    children[1] = new StaticAABBNode();
    children[1]->buildTree(right, currDepth+1);
  }

  inline bool isLeaf() const {return children[0]==NULL;}

  inline bool intersect(const Ray& ray) {
    if (isLeaf()) {
      for (size_t i=0; i < leafObjs.size(); i++) {
        if (leafObjs[i]->intersect(ray)) {
          return true;
        }
      }
      return false;
    } else if (aabb.intersect(ray)) {
      return (children[0]->intersect(ray) || children[1]->intersect(ray));
    } else {
      return false;
    }
  }

  inline bool intersect(const Ray& ray, double* tHit, Primitive** p) {
    if (isLeaf()) {

      double tempThit;
      Intersection tempIn;

      Primitive* minHitObj = NULL;
      double minThit = std::numeric_limits<double>::infinity();
      LocalGeo minLocalGeo;

      for (size_t i=0; i < leafObjs.size(); i++) {
        if (leafObjs[i]->intersect(ray,&tempThit,&tempIn)) {
          if (tempThit < minThit) {
            minThit = tempThit;
            minHitObj = tempIn.getPrimitive();
            minLocalGeo = tempIn.getLocalGeo();
          }
        }
      }

      if (minHitObj != NULL) {
        *p = minHitObj;
        *tHit = minThit;
        //in->setPrimitive(minHitObj);
        //in->setLocalGeo(minLocalGeo);
        return true;
      }

      return false;

      // Intersection in;
      // if (obj->intersect(ray,tHit,&in)) {
      //   *p = obj;
      //   //std::cout << obj << std::endl;
      //   return true;
      // } else {
      //   return false;
      // }

    } else if (aabb.intersect(ray)) {
      double t0;
      Primitive* p0;
      double t1;
      Primitive* p1;
      bool b0 = children[0]->intersect(ray,&t0,&p0);
      bool b1 = children[1]->intersect(ray,&t1,&p1);

      if (b0 && b1) {
        if (t0 < t1) {
          *p = p0;
          *tHit = t0;
          return true;
        } else {
          *p = p1;
          *tHit = t1;
          return true;
        }
      } else if (b0) {
        *p = p0;
        *tHit = t0;
        return true;
      } else if (b1) {
        *p = p1;
        *tHit = t1;
        return true;
      }
    } 
    return false;
  }

};

}

#endif
