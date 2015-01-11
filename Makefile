CC = g++
CFLAGS = -g -Wall -I ./include/ -I ./lodepng/ -I ./eigen/ -02
#-Iutil_classes -Icore -Iinterface -Ipng++ -Ialgebra3 -fopenmp 
LDFLAGS = 
#-g -Wall

OUTPUT = as2
SOURCES = src/main.cpp  src/scene.cpp lodepng/lodepng.cpp src/film.cpp src/color.cpp src/sampler.cpp src/camera.cpp src/light.cpp src/shapes/circle.cpp src/shapes/triangle.cpp src/geoprimitive.cpp src/aggprimitive.cpp src/raytracer.cpp src/objprimitive.cpp
#SOURCES = $(shell find . -name *.cpp)
#SOURCES=$(wildcard src/*.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

RM = /bin/rm -f
all: build $(OUTPUT)
build:
	@mkdir -p bin
	@mkdir -p bin/src
	@mkdir -p bin/lodepng
	@mkdir -p bin/src/shapes
$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTPUT) #$^ #$(LDFLAGS)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OUTPUT) out.png src/*.o src/shapes/*.o lodepng/*.o