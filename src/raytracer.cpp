#include "raytracer.h"

using namespace stl;

RayTracer::RayTracer() : allObjs(), lights(0), maxDepth(0) {}

RayTracer::RayTracer(AggPrimitive& allObjs_, std::vector<Light*>& lights_, int maxDepth_) : allObjs(allObjs_), lights(lights_), maxDepth(maxDepth_) {}

void RayTracer::trace(Ray& ray, Color& color, int currDepth) {
  double tHit;
  Intersection in;
  if (currDepth<maxDepth && allObjs.intersect(ray, &tHit, &in)) {
    const LocalGeo& lg = in.getLocalGeo();
    const BRDF& brdf = in.getPrimitive()->getBRDF(lg);

    Ray nextRay = Ray();
    Color nextColor = Color();
    for (size_t i=0; i<lights.size(); i++) {
      lights[i]->generateLightRay(in.getLocalGeo(),nextRay,nextColor); // Shadow Ray
      
      color+=brdf.getKa()*nextColor;
      
      if (lights[i]->isAmbient()){
        continue;
      }
      else if (!allObjs.intersect(nextRay)) {
        Vector lDir = nextRay.getDirection();
        double c_2 = std::max(0.0, (lDir).dot(lg.getNormal()));
        color+= brdf.getKd()*nextColor*c_2;

        Vector reflection = (Vector)(-lDir + lg.getNormal()*(lDir.dot(lg.getNormal()))*2.0);
        double c_3 = pow(std::max(0.0, -reflection.dot(ray.getDirection())), brdf.getSp());
        color+= brdf.getKs()*nextColor*c_3;

        if (lights[i]->isPoint()){ 
          FallOfType type = lights[i]->getFallOfType();
          double r = nextRay.getTmax();
          if (type == LINEAR) {
            color /= r;
          } else if (type == QUADRATIC) {
            color /= (r*r);
          }
        }
      }
    }

    if (brdf.getKr()!=Color(0)){
      createReflectedRay(lg, ray, nextRay);
      nextColor = Color(0);
      trace(nextRay, nextColor, currDepth + 1);
      color += brdf.getKr() * nextColor;
    }

    // If brdf.kf > 0:
    //createRefractedRay(lg, ray, nextRay);
    //trace(nextRay, nextColor, currDepth + 1);
    //color += brdf.getKf() * nextColor;
  }
}

void RayTracer::createReflectedRay(const LocalGeo& localGeo, const Ray& ray, Ray& newRay) {
  Vector reflection = (Vector)(ray.getDirection() - ray.getDirection().dot(localGeo.getNormal())*localGeo.getNormal()*2.0);
  newRay = Ray(localGeo.getPosition(),reflection,EPSILON);
}

void RayTracer::createRefractedRay(const LocalGeo& localGeo, const Ray& ray, Ray& newRay, double n) {

}

