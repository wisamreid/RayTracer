#include "scene.h"
#include <fstream>
#include <sstream>

#include "color.h"
#include "point.h"
#include "vector.h"
#include "normal.h"
#include "transform.h"

#include "material.h"
#include "ray.h"
#include "light.h"
#include "shapes/circle.h"
#include "shapes/triangle.h"
#include "geoprimitive.h"
#include "aggprimitive.h"
#include "objprimitive.h"

#define DEFAULT_W 100
#define DEFAULT_H 100

using namespace stl;

// This is the main rendering loop
void Scene::render() {
  Sample sample;
  Ray ray;
  Color color;
  while (sampler->generateSample(sample)) {
    color = Color(0);
    camera->generateRay(sample, ray);
    raytracer->trace(ray, color, 0);
    film->commit(sample, color);
  }
  film->writeImage(outputName);
}

void Scene::loadSCN(std::string filename) {
  int width=DEFAULT_W, height=DEFAULT_H;
  int depth = 5;
  int samplesPerPixel = 1;

  std::stringstream numstr;
  std::string tempstr;
  int circleCount = 1;
  int triangleCount = 1;
  int objCount = 1;

  Transform3d transform;
  transform.setIdentity();

  std::vector<Light*> lights;
  std::vector<Primitive*> objs;
  std::vector<Material*> materials;
  materials.push_back(new Material());

  std::ifstream scnFile(filename.c_str());
  if (scnFile.is_open()) {
    std::string line;
    while (std::getline(scnFile,line)) {
      char delim = ' ';
      std::replace(line.begin(),line.end(),'\t',delim); //Replace tabs with delimiter
      std::stringstream paramStream(line);

      std::string item;
      std::vector< std::string > items;
      while(std::getline(paramStream, item, delim)) {
        if (item.size() < 1){
          continue;
        }
        else if (item[0] == '#'){
          break;
        }
        else {
          items.push_back(item);
        }
      }

      if (items.size() < 1) {
        continue;
      }
      else if (items[0].compare("outputdims") == 0) {
        width = atoi(items[1].c_str());
        height = atoi(items[2].c_str());
      }
      else if (items[0].compare("outputname") == 0) {
        outputName = items[1];
      }
      else if (items[0].compare("rdepth") == 0) {
        depth = atoi(items[1].c_str());
      }
      else if (items[0].compare("antialias") == 0) {
        samplesPerPixel = atoi(items[1].c_str());
      }
      else if (items[0].compare("cam") == 0) {
        Point eye = Point(atof(items[1].c_str()),
                          atof(items[2].c_str()),
                          atof(items[3].c_str()));
        Point ll = Point(atof(items[4].c_str()),
                         atof(items[5].c_str()),
                         atof(items[6].c_str()));
        Point lr = Point(atof(items[7].c_str()),
                         atof(items[8].c_str()),
                         atof(items[9].c_str()));
        Point ul = Point(atof(items[10].c_str()),
                         atof(items[11].c_str()),
                         atof(items[12].c_str()));
        Point ur = Point(atof(items[13].c_str()),
                         atof(items[14].c_str()),
                         atof(items[15].c_str()));
        camera = new Camera(eye,ll,lr,ul,ur,width,height);
      }
      else if (items[0].compare("sph") == 0) {
        Point c = Point(atof(items[1].c_str()),
                        atof(items[2].c_str()),
                        atof(items[3].c_str()));
        double r = atof(items[4].c_str());
        Circle* s = new Circle(c,r);
        Transform t = Transform(transform);
        numstr << circleCount;
        tempstr = "sphere"+numstr.str();
        numstr.str(std::string()); // Clear the stream variable
        objs.push_back(new GeoPrimitive(s,materials.back(),t,tempstr));
        circleCount++;
      }
      else if (items[0].compare("tri") == 0) {
        Point p1 = Point(atof(items[1].c_str()),
                         atof(items[2].c_str()),
                         atof(items[3].c_str()));
        Point p2 = Point(atof(items[4].c_str()),
                         atof(items[5].c_str()),
                         atof(items[6].c_str()));
        Point p3 = Point(atof(items[7].c_str()),
                         atof(items[8].c_str()),
                         atof(items[9].c_str()));
        Triangle* s = new Triangle(p1,p2,p3);
        Transform t = Transform(transform);
        numstr << triangleCount;
        tempstr = "triangle"+numstr.str();
        numstr.str(std::string()); // Clear the stream variable
        objs.push_back(new GeoPrimitive(s,materials.back(),t,tempstr));
        triangleCount++;
      }
      else if (items[0].compare("obj") == 0) {
        std::vector<Primitive*> faces;
        loadOBJ(items[1],materials,faces);

        Transform t = Transform(transform);
        numstr << objCount;
        tempstr = "obj"+numstr.str();
        numstr.str(std::string()); // Clear the stream variable
        objs.push_back(new ObjPrimitive(faces,t,tempstr));
        objCount++;
      }
      else if (items[0].compare("ltp") == 0) {
        Point pos = Point(atof(items[1].c_str()),
                          atof(items[2].c_str()),
                          atof(items[3].c_str()));
        Color intensity = Color(atof(items[4].c_str()),
                                atof(items[5].c_str()),
                                atof(items[6].c_str()));
        FallOfType fot;
        if (items.size()>7) {
          unsigned int parsedFot = atoi(items[7].c_str());
          if (parsedFot == 2)
            fot = QUADRATIC;
          else if (parsedFot == 1)
            fot = LINEAR;
          else
            fot = NONE;
        }
        else {
          fot = NONE;
        }
        lights.push_back(new PointLight(pos,intensity,fot));
        lights.back()->setTransform(Transform(transform));
      }
      else if (items[0].compare("ltd") == 0) {
        Vector dir = Vector(atof(items[1].c_str()),
                            atof(items[2].c_str()),
                            atof(items[3].c_str()));
        Color intensity = Color(atof(items[4].c_str()),
                                atof(items[5].c_str()),
                                atof(items[6].c_str()));
        lights.push_back(new DirectionLight(dir,intensity));
        lights.back()->setTransform(Transform(transform));
      }
      else if (items[0].compare("lta") == 0) {
        Color intensity = Color(atof(items[1].c_str()),
                                atof(items[2].c_str()),
                                atof(items[3].c_str()));
        lights.push_back(new AmbientLight(intensity));
      }
      else if (items[0].compare("mat") == 0) {
        Color ka = Color(atof(items[1].c_str()),
                         atof(items[2].c_str()),
                         atof(items[3].c_str()));
        Color kd = Color(atof(items[4].c_str()),
                         atof(items[5].c_str()),
                         atof(items[6].c_str()));
        Color ks = Color(atof(items[7].c_str()),
                         atof(items[8].c_str()),
                         atof(items[9].c_str()));
        double sp = atof(items[10].c_str());
        Color kr = Color(atof(items[11].c_str()),
                         atof(items[12].c_str()),
                         atof(items[13].c_str()));
        BRDF brdf = BRDF(ka,kd,ks,sp,kr);
        materials.push_back(new Material(brdf));
      }
      else if (items[0].compare("xft") == 0) {
        transform *= Eigen::Translation3d(atof(items[1].c_str()),
                                          atof(items[2].c_str()),
                                          atof(items[3].c_str())
                                         );
      }
      else if (items[0].compare("xfr") == 0) {
        Vector axis(atof(items[1].c_str()),atof(items[2].c_str()),atof(items[3].c_str()));
        double amount = axis.norm();
        transform *= Eigen::AngleAxisd(amount,axis/amount);
      }
      else if (items[0].compare("xfs") == 0) {
        transform *= Eigen::Scaling(atof(items[1].c_str()),
                                    atof(items[2].c_str()),
                                    atof(items[3].c_str())
                                   );
      }
      else if (items[0].compare("xfz") == 0) {
        transform.setIdentity();
      }
      else {
        std::cerr << "Unknown type: " << items[0] << std::endl;
        continue;
      }
      std::cout << items[0] << std::endl;
    }
    scnFile.close();
  }
  else std::cout << "Unable to open file" << std::endl;

  if (outputName.size()<1) {
    outputName = "out.png";
  }
  sampler = new Sampler(width,height,samplesPerPixel);
  if (camera == NULL) {
    camera = new Camera(width,height);
  }
  camera->setShape(width,height); // Incase width/height changed after creation of camera
  film = new Film(width,height,samplesPerPixel);
  AggPrimitive setOfObjs = AggPrimitive(objs,"group 1");
  raytracer = new RayTracer(setOfObjs,lights,depth);
}

void Scene::loadOBJ(std::string filename, std::vector<Material*>& materials, std::vector<Primitive*>& faces) {
  std::string name = "obj";
  std::vector<Point> verticies;
  std::vector<Normal> normals;
  //std::vector<Texture> uvs;

  std::ifstream scnFile(filename.c_str());
  if (scnFile.is_open()) {
    std::string line;
    while (std::getline(scnFile,line)) {
      char delim = ' ';
      std::replace(line.begin(),line.end(),'\t',delim); //Replace tabs with delimiter
      std::stringstream paramStream(line);

      std::string item;
      std::vector< std::string > items;
      while(std::getline(paramStream, item, delim)) {
        if (item.size() < 1){
          continue;
        }
        else if (item[0] == '#'){
          break;
        }
        else {
          items.push_back(item);
        }
      }

      if (items.size() < 1) {
        continue;
      }
      else if (items[0].compare("o") == 0) {
        name = items[1];
      }
      else if (items[0].compare("g") == 0) {
        std::cout << "Group name: " << items[1] << std::endl;
      }
      else if (items[0].compare("v") == 0) {
        //Parse vector
        double x = std::atof(items[1].c_str());
        double y = std::atof(items[2].c_str());
        double z;
        if (items.size()>3) {
          z = std::atof(items[3].c_str());
        }
        else {
          z = 0.0;
        }
        verticies.push_back(Point(x,y,z));
        //std::cout << "Point: " << x << y << z << std::endl;
      }
      else if (items[0].compare("vt") == 0) {
        double u = std::atof(items[1].c_str());
        double v = std::atof(items[2].c_str());
        std::cout << "Texture: " << u << v << std::endl;
      }
      else if (items[0].compare("vn") == 0) {
        double x = std::atof(items[1].c_str());
        double y = std::atof(items[2].c_str());
        double z = std::atof(items[3].c_str());
        normals.push_back(Normal(x,y,z));
        //std::cout << "Normal: " << x << y << z << std::endl;
      }
      else if (items[0].compare("f") == 0) {
        char delim = '/';
        std::string index;
        int vertexInd[3];
        int countV = 0;
        int textureInd[3];
        int countT = 0;
        int normalInd[3];
        int countN = 0;
        for (size_t i=1; i<items.size(); i++){
          std::stringstream faceStream(items[i]);
          if (std::getline(faceStream, index, delim)){
            vertexInd[countV++] = std::atoi(index.c_str())-1;
          }
          if (std::getline(faceStream, index, delim) && index.size()>0){
            textureInd[countT++] = std::atoi(index.c_str())-1;
          }
          if (std::getline(faceStream, index, delim) && index.size()>0){
            normalInd[countN++] = std::atoi(index.c_str())-1;
          }
        }

        Triangle* face;
        if (countV == 3) {
          if (countN == 3) {
            face = new Triangle(verticies[vertexInd[0]],verticies[vertexInd[1]],verticies[vertexInd[2]],normals[normalInd[0]],normals[normalInd[1]],normals[normalInd[2]]);
          } else {
            face = new Triangle(verticies[vertexInd[0]],verticies[vertexInd[1]],verticies[vertexInd[2]]);
          }
        }
        faces.push_back(new GeoPrimitive(face,materials.back(),""));
      }
      else if (items[0].compare("mtllib") == 0) {
        std::cout << "MTL file: " << items[1] << std::endl;
      }
      else if (items[0].compare("usemtl") == 0) {
        std::cout << "Material: " << items[1] << std::endl;
      }
      else {
        std::cerr << "Unknown type: " << items[0] << std::endl;
        continue;
      }
    }
    scnFile.close();
  }
  else std::cout << "Unable to open file" << std::endl; 
}

void Scene::loadMTL(std::string filename) {
  //TODO
}