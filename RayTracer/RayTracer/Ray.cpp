#include "Ray.h"


Ray::Ray(glm::vec4 newOrigin, glm::vec4 newDirection)
{
	origin = newOrigin;
	direction = newDirection;
}


Ray::~Ray(void)
{
}
