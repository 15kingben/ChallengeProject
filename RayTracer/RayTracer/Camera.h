#pragma once
#include <glm\glm.hpp>

class Camera
{

public:
	glm::vec3 lookFrom;
	glm::vec3 lookAt;
	glm::vec3 up;
	float fovy;
	float aspect;
	Camera(glm::vec3, glm::vec3, glm::vec3 , float, float);
	Camera(void);
	~Camera(void);
};