#pragma once
#include <glm\glm.hpp>
class Light
{
	
	

	public:
		glm::vec4 loc    ;//w coord is 0 if directional
		glm::vec3 color  ;
		enum Type{point,direction};
		Type type;
		float constAtten ;
		float linAtten   ;
		float quadAtten  ;
		Light(glm::vec4 , glm::vec3, float,float,float,Type);
		~Light(void);


};

