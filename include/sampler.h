#ifndef SAMPLER_H
#define SAMPLER_H

#include "sample.h"

// stl :: string theory labs (taking over a universe near you) 
namespace stl
{

class Sampler {
 private:
  int maxW, maxH, spp; //Samples Per Point
 public:
  Sampler(int w_, int h_);
  Sampler(int w_, int h_, int spp_);
  bool generateSample(Sample& sample);
};

}

#endif
