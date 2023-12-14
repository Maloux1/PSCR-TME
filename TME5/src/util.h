#pragma once

#include "Vec3D.h"
#include "Rayon.h"
#include "Scene.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <random>

using namespace std;
using namespace pr;

void fillScene(Scene & scene, default_random_engine & re);
int findClosestInter(const Scene & scene, const Rayon & ray);
Color computeColor(const Sphere & obj, const Rayon & ray, const Vec3D & camera, std::vector<Vec3D> & lights);
void exportImage(const char * path, size_t width, size_t height, Color * pixels);