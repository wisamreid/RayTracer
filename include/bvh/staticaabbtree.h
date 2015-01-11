#ifndef STATICAABBTREE_H
#define STATICAABBTREE_H

#include "bvh/staticaabbnode.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class StaticAABBTree {
 private:
  StaticAABBNode* root;

 public:
  StaticAABBTree() : root(NULL) {};
  StaticAABBTree(std::vector<Primitive*>& objs) : root(NULL) {root = new StaticAABBNode(); root->buildTree(objs,0); };

  inline bool intersect(const Ray& ray) {return (root && root->intersect(ray));};
  inline bool intersect(const Ray& ray, double* tHit, Intersection* in) {
    Primitive* p;
    double t;
    if (root && root->intersect(ray, &t, &p)) {
      return p->intersect(ray,tHit,in);
    } else {
      return false;
    }
  };

  inline const AABB& getAABB() const {return root->aabb;};

};

}

#endif
