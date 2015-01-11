#ifndef DYNAMICAABBTREE_H
#define DYNAMICAABBTREE_H

#include "bvh/dynamicaabbnode.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class DynamicAABBTree {
 private:
  DynamicAABBNode* root;
  double margin;
  std::vector<DynamicAABBNode*> nodesToReinsert;

  inline void updateHelper(DynamicAABBNode* node) {
    if (!node->isLeaf()) {
      updateHelper(node->children[0]);
      updateHelper(node->children[1]);
    } else if (!node->aabb.contains(node->obj->getAABB())) {
      nodesToReinsert.push_back(node);
    }
  };

  inline void insertNode(DynamicAABBNode* node, DynamicAABBNode** parent) {
    DynamicAABBNode* p = *parent;
    if (p->isLeaf()) {
      DynamicAABBNode* newNode = new DynamicAABBNode();
      newNode->parent = p->parent;
      newNode->makeBranch(node,p);
      *parent = newNode;
    } else {
      AABB* aabb0 = &p->children[0]->aabb;
      AABB* aabb1 = &p->children[1]->aabb; 
      float changeInVol0 = aabb0->merge(node->aabb).volume() - aabb0->volume();
      float changeInVol1 = aabb1->merge(node->aabb).volume() - aabb1->volume();

      if (changeInVol0 < changeInVol1)
        insertNode(node, &p->children[0]);
      else
        insertNode(node, &p->children[1]);
    }
    (*parent)->updateAABB(margin);
  };

 public:
  DynamicAABBTree() : root(NULL), margin(0.3) {};
  DynamicAABBTree(std::vector<Primitive*> objs) : root(NULL), margin(0.3) {for(size_t i=0; i<objs.size(); i++){add(objs[i]);} };

  inline void add(Primitive* obj) {
    if (root) {
      DynamicAABBNode *newNode = new DynamicAABBNode(obj);
      newNode->updateAABB(margin);
      insertNode(newNode, &root);
    } else {
      root = new DynamicAABBNode(obj);
      root->updateAABB(margin);
    }
  };

  inline void update() {
    if (root) {
      if (root->isLeaf())
        root->updateAABB(margin);
      else {
        nodesToReinsert.clear();
        DynamicAABBNode* node;
        DynamicAABBNode* p;
        DynamicAABBNode* s;
        DynamicAABBNode**pp;
        updateHelper(root);
        for (size_t i = 0; i<nodesToReinsert.size(); i++){
          node = nodesToReinsert[i];
          p=node->parent;
          s=node->sibling();

          // Remove the incorrect node
          if (p->parent) {
            s->parent = p->parent;
            if (p == p->parent->children[0]) {
              pp = &p->parent->children[0];
            } else {
              pp = &p->parent->children[1];
            }
          } else {
            s->parent = NULL;
            pp = &root;
          }
          *pp = s;
          delete p;

          node->updateAABB(margin);
          insertNode(node, &root);
        }
      }
    }
  };

  inline bool intersect(const Ray& ray) {return (root && root->intersect(ray));};
  inline bool intersect(const Ray& ray, double* tHit, Intersection* in) {
    //std::cout << std::endl;
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
