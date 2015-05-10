#pragma once
#include "glm-0.9.2.7\glm\glm.hpp"
#include "Ray.h"

class shape
{
public:

	//intersect and reflection methods
	glm::vec3 ambient ; 
	glm::vec3 diffuse ; 
	glm::vec3 specular;
	glm::vec3 emission; 
	float shininess ;
	
	glm::mat4 transform ;
	glm::mat4 transformInv;
	//glm::vec4 compLight(glm::vec4,glm::vec4,glm::vec4,glm::vec4,glm::vec4);
	virtual glm::vec3 getNormal(glm::vec3 point) = 0;
	virtual bool Intersect(Ray,glm::vec3&) = 0;
	//virtual glm::vec3 findColor(glm::vec4) = 0;
	virtual ~shape(void);
};

