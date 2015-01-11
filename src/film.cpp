#include "film.h"
#include <cmath>

using namespace stl;

Film::Film(int width_, int height_): width(width_), height(height_), spp(1), imageBuffer(width*height*3) {}
Film::Film(int width_, int height_, int spp_): width(width_), height(height_), spp(spp_), imageBuffer(width*height*3) {}
void Film::commit(Sample& sample, Color& color) {
  double r = std::min(1.0,std::max(0.0,color.getR()));
  double g = std::min(1.0,std::max(0.0,color.getG()));
  double b = std::min(1.0,std::max(0.0,color.getB()));
  int pixel = std::floor(sample.getY())*width*3+std::floor(sample.getX())*3;
  imageBuffer[pixel+0] += r;
  imageBuffer[pixel+1] += g;
  imageBuffer[pixel+2] += b;
}

void Film::writeImage(std::string filename) {
  std::vector<int> image;
  image.resize(width*height);
  for (int x=0; x<width; x++) {
    for (int y=0; y<height; y++){
      int pixel = y*width*3+x*3;
      double r = imageBuffer[pixel+0]/spp;
      double g = imageBuffer[pixel+1]/spp;
      double b = imageBuffer[pixel+2]/spp;
      int rgba = (int)(r*255+0.5)|(int)(g*255+0.5)<<8|(int)(b*255+0.5)<<16|255<<24;
      image[y*width+x] = rgba;
    }
  }

  //Save the image
  unsigned error = lodepng::encode(filename.c_str(), (unsigned char*)&image[0], width, height);

  if (error) {
    std::cout << "PNG error " << error << ": "<< lodepng_error_text(error) << std::endl;
  }
}