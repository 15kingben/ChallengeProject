#pragma once
#include "shape.h"
#include "Ray.h"
class Triangle : public shape
{
	public:
		glm::vec3 na,nb,nc;
		glm::vec3 a,b,c;
		glm::vec3 getNormal(glm::vec3);
		bool Intersect(Ray ray,glm::vec3&);
		glm::mat4 getTransform();
		Triangle(glm::vec3 ,glm::vec3 , glm::vec3 , glm::mat4 , glm::vec3,glm::vec3,glm::vec3,glm::vec3,float);//triangle
		Triangle(glm::vec3 ,glm::vec3 , glm::vec3 , glm::vec3 , glm::vec3 , glm::vec3 ,glm::mat4,glm::vec3,glm::vec3,glm::vec3,glm::vec3,float);//trinormal
		~Triangle(void);
};

