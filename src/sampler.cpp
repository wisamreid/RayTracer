#include <sampler.h>
#include <cstdlib>
#include <iostream>

using namespace stl;

Sampler::Sampler(int w_, int h_): maxW(w_), maxH(h_), spp(1) {}
Sampler::Sampler(int w_, int h_, int spp_): maxW(w_), maxH(h_), spp(spp_) {}
bool Sampler::generateSample(Sample& sample) {
  static int currX = 0;
  static int currY = 0;
  // static int currX = 49;
  // static int currY = 49;
  // maxW = 51;
  // maxH = 51;

  static int currS = 0;

  // Print percent left
  if (((maxW*maxH*currS + currY*maxW+currX) % (maxW*maxH*spp/100))==0){
    std::cout << 1.0*(maxW*maxH*currS + currY*maxW+currX)/(maxW*maxH*spp)*100 << "%" << std::endl;
  }

  if (currX >= maxW) {currX=0; currY++;}
  if (currY >= maxH) {currY=0; currS++;}
  if (currS >= spp) {return false;}
  if (spp==1){
    sample.setX(currX + 0.5);
    sample.setY(currY + 0.5);
  } else {
    double randX = ((double)rand()/(RAND_MAX)); //Between 0 and 1
    double randY = ((double)rand()/(RAND_MAX)); //Between 0 and 1
    sample.setX(currX + randX);
    sample.setY(currY + randY);
  }
  currX++;
  return true;
}
