#include "Camera.h"
#include <glm\glm.hpp>

Camera::Camera(glm::vec3 _lookFrom,glm::vec3 _lookAt,glm::vec3 _up,float _fovy,float _aspect)
{
	lookFrom = _lookFrom;
	lookAt = _lookAt;
	up = _up;
	fovy = _fovy;
	aspect = _aspect;
}

Camera::Camera(void)
{

}

Camera::~Camera(void)
{
}
