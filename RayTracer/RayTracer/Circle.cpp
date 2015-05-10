#include "Circle.h"
#include "Variables.h"
#include <iostream>

Circle::Circle(float _x, float _y, float _z, float _radius,glm::mat4 _transform,glm::vec3 amb,glm::vec3 diff,glm::vec3 spec,glm::vec3 emiss, float shine)
{
	x = _x;
	y = _y;
	z = _z;
	radius = _radius;
	transform = _transform;
	transformInv = glm::inverse(transform);
	// Set the object's light properties
	ambient  = amb; 
	diffuse  = diff; 
	specular = spec; 
	emission = emiss;
	
	shininess = shine; 
}

bool Circle::Intersect(Ray ray , glm::vec3 &point){
	
	ray.origin  =    ray.origin*transformInv  ;   
	ray.direction =  ray.direction*transformInv ;
	ray.origin = glm::vec4(ray.origin.x/ray.origin.w, ray.origin.y/ray.origin.w, ray.origin.z/ray.origin.w, 1.0);
	//glm::normalize(ray.origin);


	float tpos,tneg,discriminant;
	float a = glm::dot(ray.direction,ray.direction);
	float b = 2 * glm::dot(glm::vec3(ray.direction),(glm::vec3(ray.origin) - glm::vec3(x,y,z)));
	float c = glm::dot(  (glm::vec3(ray.origin) - glm::vec3(x,y,z)) , (glm::vec3(ray.origin) - glm::vec3(x,y,z))  ) - radius*radius;
	
	discriminant = b*b - 4 * a * c;
	if(discriminant < -.0001)//if discriminant < 0, return -1 or false
		return false;
	discriminant = fabs(discriminant);
	tpos = (-b + sqrt(discriminant))/(2*a);
	tneg = (-b - sqrt(discriminant))/(2*a);
	
	
		
		float tmin = std::min(tpos,tneg);
	if(tmin < 0.01)
		return false;
	//glm::vec4 normal = (ray.origin + (ray.direction)*tmin) - glm::vec4(x,y,z,1);//intersection - center
	glm::vec4 pointTrans = (ray.origin + ray.direction *tmin)*transform;
	point = glm::vec3(pointTrans/pointTrans.w);
	return true;
}

glm::vec3 Circle::getNormal(glm::vec3 point)
{
	glm::vec4 point4 = glm::vec4(point,1) * transformInv;
	point4 /= point4.w;
	point = glm::vec3(point4);
	return glm::vec3(glm::vec4(  glm::vec3(point) - glm::vec3(x,y,z)  ,0.0f) * glm::transpose(transformInv) );
}


Circle::~Circle(void)
{
}
