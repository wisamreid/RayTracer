#ifndef BRDF_H
#define BRDF_H

#include "color.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class BRDF {
 private:
  Color ka;
  Color kd;
  Color ks;
  double sp;
  Color kr;
 public:
  BRDF() : ka(), kd(), ks(), sp(1.0), kr() {};
  BRDF(Color& ka_, Color& kd_, Color& ks_, double sp_, Color& kr_) : ka(ka_), kd(kd_), ks(ks_), sp(sp_), kr(kr_) {};
  const Color& getKa() const {return ka;};
  const Color& getKd() const {return kd;};
  const Color& getKs() const {return ks;};
  const double getSp() const {return sp;};
  const Color& getKr() const {return kr;};
};

}

#endif
