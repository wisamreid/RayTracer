#ifndef FILM_H
#define FILM_H

#include "lodepng.h"
#include "color.h"
#include "sample.h"

// stl :: string theory labs (taking over a universe near you)
namespace stl
{

class Film {
 private:
  int width, height, spp; //Samples Per Pixel
  std::vector<double> imageBuffer;
 public:
  Film(int width, int height);
  Film(int width, int height, int samplesPerPixel);
  void commit(Sample& sample, Color& color);
  void writeImage(std::string filename);
};

}

#endif
