#ifndef DYNAMICAABBNODE_H
#define DYNAMICAABBNODE_H

#include "bvh/aabb.h"
#include "primitive.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class DynamicAABBNode {
 public:
  DynamicAABBNode* parent;
  DynamicAABBNode* children[2];

  AABB aabb;
  Primitive* obj; // Leaf nodes only

  DynamicAABBNode() : parent(NULL) {children[0]=NULL;children[1]=NULL;};
  DynamicAABBNode(Primitive* obj_) : parent(NULL), obj(obj_) {children[0]=NULL;children[1]=NULL;};
  inline bool isLeaf() const {return children[0]==NULL;}
  inline void makeBranch(DynamicAABBNode* n0, DynamicAABBNode* n1) {children[0]=n0; children[1]=n1; n0->parent=this; n1->parent=this;}
  inline void updateAABB(float margin) {
    if(!isLeaf()){
      aabb = children[0]->aabb.merge(children[1]->aabb);
    } else {
      Vector mVec(margin);
      Vector min = (Vector)(obj->getAABB().getMin()-mVec);
      Vector max = (Vector)(obj->getAABB().getMax()+mVec);
      aabb.setMin(min);
      aabb.setMax(max);
    }
  };
  inline DynamicAABBNode* sibling() const {return this==parent->children[1] ? parent->children[0] : parent->children[1]; }

  inline bool intersect(const Ray& ray) {
    if (isLeaf()) {
      return obj->intersect(ray);
    } else if (aabb.intersect(ray)) {
      return (children[0]->intersect(ray) || children[1]->intersect(ray));
    } else {
      return false;
    }
  }

  inline bool intersect(const Ray& ray, double* tHit, Primitive** p) {
    if (isLeaf()) {
      Intersection in;
      if (obj->intersect(ray,tHit,&in)) {
        *p = obj;
        //std::cout << obj << std::endl;
        return true;
      } else {
        return false;
      }
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
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

};

}

#endif
