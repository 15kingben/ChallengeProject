#pragma once
#include "shape.h"
#include "Camera.h"
#include <vector>
#include "Light.h"
#include <string>

class Scene
{
public:

	Camera cam;
	std::string filename;
	int maxdepth;
	std::vector<shape*> objects;
	std::vector<Light> lights;
	Scene(void);
	~Scene(void);
};

