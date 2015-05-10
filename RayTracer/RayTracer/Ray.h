#pragma once
#include "glm-0.9.2.7\glm\glm.hpp"

class Ray
{
public:
	glm::vec4 origin;
	glm::vec4 direction;
	Ray(glm::vec4 , glm::vec4 );
	~Ray(void);
};

