#ifndef SCENE_H
#define SCENE_H

#include "sampler.h"
#include "camera.h"
#include "film.h"
#include "raytracer.h"
#include "primitive.h"
#include "material.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class Scene {
 private:
  std::string outputName;
  Sampler* sampler;
  Camera* camera;
  Film* film;
  RayTracer* raytracer;
 public:
  void render();
  void loadSCN(std::string filename);
  void loadOBJ(std::string filename, std::vector<Material*>& materials, std::vector<Primitive*>& faces);
  void loadMTL(std::string filename);
};

}

#endif
