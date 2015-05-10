#pragma once
#include "shape.h"

class Circle : public shape
{
public:
	float x , y , z , radius;
	
	
	glm::vec3 getNormal(glm::vec3);
	glm::mat4 getTransform();
	Circle(float,float,float,float,glm::mat4,glm::vec3,glm::vec3,glm::vec3,glm::vec3,float);
	bool Intersect(Ray,glm::vec3&);
	glm::vec3 findColor(glm::vec4);
	~Circle(void);
};

