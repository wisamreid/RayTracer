#ifndef MATERIAL_H
#define MATERIAL_H

#include "brdf.h"
#include "localgeo.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class Material {
 private:
  BRDF brdf;
  //Texture t;
 public:
  Material() : brdf() {};
  Material(BRDF& brdf_) : brdf(brdf_) {};
  //Material(BRDF& brdf_, Texture& t_) : brdf(brdf_), t(t_) {};
  inline const BRDF& getBRDF(const LocalGeo& l)  {return brdf;};
  //inline const Texture& getTexture(LocalGeo& l) {/*Do something*/};

};
  
}

#endif
