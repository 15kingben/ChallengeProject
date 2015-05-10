#include "Light.h"


Light::Light(glm::vec4 pos, glm::vec3 col, float con, float lin, float quad,Type _type)
{
	loc = pos;
	color = col;
	constAtten = con;
	linAtten = lin;
	quadAtten = quad;
	type = _type;
}


Light::~Light(void)
{
}
