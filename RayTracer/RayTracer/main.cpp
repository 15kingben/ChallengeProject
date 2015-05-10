
#include <array>  //for std::vector
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "parser.h"
#include "FreeImage.h"
#include "Camera.h"
#include "Scene.h"
#include "shape.h"
#include "circle.h"
#include "Triangle.h"
#include "Ray.h"
#include "Variables.h"
#include "shape.h"
#include "Transform.h"

glm::vec3 findColor(glm::vec4,shape*,Ray,int);
void raytrace(Camera,Scene,int,int);
void printVector(glm::vec3);
void printVector(glm::vec4);
glm::vec3 setColor(Ray&);
// For portability across platforms
Scene scene;
int sceneWidth;
int sceneHeight;
std::string outputFile;
const bool DEBUG = false;

int main(int argc, char* argv[]){
	std::cout << argv[1];
	scene.maxdepth = 3;
	read(argv[1]);
	
	
	
	//Triangle c = Triangle(glm::vec3(0,2,0),glm::vec3(2,0,0),glm::vec3(0,0,3));
	//std::cout << c.Intersect(Ray(glm::vec3(0,0,0),glm::vec3(1,1,.5)));
	//Triangle c = Triangle(glm::vec3(0,2,0),glm::vec3(2,0,0),glm::vec3(0,0,3));
	std::cout << glm::length(vec3(1,1,1)-vec3(2,2,2)) << std::endl;
	Circle k = Circle(0,0,0,.5,Transform::translate(2,2,2),glm::vec3(1.0),glm::vec3(1),glm::vec3(1),glm::vec3(1),1);
	glm::vec3 intersectPoint;
	bool i = k.Intersect(Ray(glm::vec4(0,0,0,1.0),glm::vec4(1.0,1.0,1.0,0)),intersectPoint);
	std::cout << i << std::endl;
	printVector(intersectPoint);
	
	//std::cout << k.normal.x << " " <<  c.normal.y << " " << c.normal.z;
	raytrace(scene.cam,scene,sceneWidth,sceneHeight);
	//std::cout << i;
	std::cin.get();




}

void printVector(glm::vec3 print)
{
	std::cout << "x " << print.x << " y " <<  print.y << " z " << print.z << std::endl;
}

void printVector(glm::vec4 print)
{
	std::cout << "x " << print.x << " y " <<  print.y << " z " << print.z << " w " << print.w  << std::endl ;
}


bool getClosestIntersect(shape* &tempObj, glm::vec3 &intersect, Ray ray)
{
	bool isHit;
	bool anyHit = false;
	bool firstHit = false;
	glm::vec3 tempIntersect;
	for(shape *object : scene.objects){

				isHit = object->Intersect(ray,tempIntersect);
				
				if(isHit){ 
					anyHit = true;

					if(!firstHit){//if intersect initialised
						firstHit = true;
						intersect = tempIntersect;
						tempObj = object;
					}else{
						//glm::normalize(ray.origin);
						if(glm::length(tempIntersect - glm::vec3(ray.origin)) < glm::length(intersect - glm::vec3(ray.origin))){
							tempObj = object;
							intersect = tempIntersect;
						}
					}				
					isHit = false;
				}
			}
	return anyHit;
}

void raytrace(Camera cam, Scene scene, int width, int height){
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);
	
	RGBQUAD color ;
	if(!bitmap)
		exit(1); //WTF?! We can't even allocate images? Die!
	//Draws a gradient from blue to green:
	glm::vec3 eye = scene.cam.lookFrom;
	glm::vec3 center = scene.cam.lookAt;
	//center.z *= -1;
	//glm::normalize(scene.cam.up);
	glm::vec3 w = glm::normalize(eye - center);
	glm::vec3 u = glm::normalize( glm::cross( scene.cam.up, w))  ;
	glm::vec3 v = glm::cross(u,w)  ;

				std::cout.setf(std::ios::boolalpha);
				//Circle *c = dynamic_cast<Circle*>(scene.objects[0]);
				//std::cout << c->x << " " << c->y << " " << c->z << " " << c->radius;
	std::cin.get();

	for ( int i = 0; i < width; i++) {
		for ( int j = 0; j < height; j++) {

			float width1 = width;
			float height1 = height;
			float fovy = scene.cam.fovy * pi / 180.0;
			float fovx = fovy * (width1/height1);
			float alpha = glm::tan(fovx/2) * ((i - width1 / 2)/(width1/2));
			float beta = glm::tan(fovy/2) * ((height1/2 - j)/(height1/2));

			Ray ray0 (  glm::vec4(eye,1.0) , glm::vec4(  ((alpha*u +  beta*v - w) + vec3(.0005,.0005,0 ) ) ,0.0 ) );
			Ray ray1 (  glm::vec4(eye,1.0) , glm::vec4(  ((alpha*u +  beta*v - w) + vec3(.0005,-.0005,0 )) ,0.0 ) );
			Ray ray2 (  glm::vec4(eye,1.0) , glm::vec4(  ((alpha*u +  beta*v - w) + vec3(-.0005,.0005,0 )) ,0.0 ) );
			Ray ray3 (  glm::vec4(eye,1.0) , glm::vec4(  ((alpha*u +  beta*v - w) + vec3(-.0005,-.0005,0 )) ,0.0 ) );
			vec3 cols[4];
			vec3 col;
			
			
			cols[0] = setColor( ray0);
			cols[1] = setColor( ray1);
			cols[2] = setColor( ray2);
			cols[3] = setColor( ray3);
			col = cols[0] + cols[1] + cols[2] + cols[3];
			col/= 4;
			color.rgbRed = col.x * 255.0;
			color.rgbGreen = col.y * 255.0;
			color.rgbBlue = col.z * 255.0;
			
			FreeImage_SetPixelColor ( bitmap , i , j , &color );
			if(i % 10 == 0 && j % 10 == 0 && i == j)
				std::cout << "x: " << i << " y: " << j << std::endl;
			// Notice how we're calling the & operator on "color"
			// so that we can pass a pointer to the color struct.
		}
	}
	if ( FreeImage_Save (FIF_PNG, bitmap , outputFile.c_str() , 0))
		std::cout << "Image successfully saved !" << std::endl ;
	FreeImage_DeInitialise(); //Cleanup !
}

glm::vec3 setColor(Ray &ray)
{

	glm::vec3 intersect;
			bool anyHit = false;
			bool firstHit = false;
			shape *tempObj = nullptr;
			vec3 col;
			anyHit = getClosestIntersect(tempObj, intersect, ray);

	if(anyHit){
				anyHit = false;
				col = findColor(glm::vec4(intersect,1),tempObj,ray,1);//if there was a hit
				
				
				//color.rgbRed = tempObj->ambient.x * 255.0;
				//color.rgbGreen = tempObj->ambient.y * 255.0;
				//color.rgbBlue = tempObj->ambient.z * 255.0;
			}else{
				col = vec3(0,0,0);
			}

	return col;

}

const bool FCDEBUG = false;
glm::vec3 findColor(glm::vec4 point, shape* obj, Ray eyeRay,int depth){
	if (depth > scene.maxdepth)
		return glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 color = obj->ambient + obj->emission;
	glm::vec3 normal = obj->getNormal(glm::vec3(point));
	//point = point*obj->transform;
	//point /= point.w;
	 
	for(Light l : scene.lights){
		bool intersect = false;
		glm::vec3 hitpoint;
		bool hit;
		shape* tempObj;
			glm::vec4 dir = l.loc - point;
			dir.w = 0;
			dir = glm::normalize(dir);
			hit = getClosestIntersect(tempObj, hitpoint, Ray(point + (.00001 * dir), dir));
			if(hit){
					float hitToLight = abs(glm::length(glm::vec3(l.loc) - vec3(hitpoint)));
					float pointToLight = abs(glm::length(vec3(l.loc) - glm::vec3(point)));
					if(FCDEBUG){
						std::cout << hitToLight   << "\n";
						std::cout << pointToLight << "\n";
						std::cin.get();
					}
					if(hitToLight < pointToLight )//&& glm::length(glm::vec3(point) - hitpoint) > 0
						intersect = true;
			}
		if(!intersect){
			if(FCDEBUG){
				std::cout << "light";
				std::cin.get();
			}
			float distance = glm::length(glm::vec3(glm::vec3(l.loc) - glm::vec3(point)));

			float attenuation = (1.0/(l.constAtten + distance * l.linAtten + distance*distance*l.quadAtten));
			if(FCDEBUG)
				std::cout << attenuation << "\n" << l.constAtten << "\n" << l.linAtten << "\n" << l.quadAtten << "\n";
			//std::cin.get();
			normal = glm::normalize(normal);
			
			glm::vec3 direction;
			if(l.type == Light::direction)
				direction = glm::normalize(glm::vec3(l.loc));
			else
				direction = glm::normalize(glm::vec3(l.loc) - glm::vec3(point));
			float nDotL = glm::max(glm::dot(normal, direction),0.0f);
			glm::vec3 halfvec = glm::normalize(direction - glm::normalize(glm::vec3(eyeRay.direction)));
			float nDotH = glm::max(glm::dot(normal, halfvec),0.0f);
			glm::vec3 diffuse = obj->diffuse * nDotL * l.color;
			glm::vec3 specular =  obj->specular * glm::pow(nDotH,obj->shininess) * l.color;
			if(l.type == Light::point)//(l.loc.w < .01 && l.loc.w > -.01)
				color += (diffuse + specular) * attenuation;
			else
				color += (diffuse + specular);
		}

	}

	//recursive bit
	vec3 refDir = glm::normalize(vec3(eyeRay.direction));
	refDir = refDir - 2.0f * normal * glm::dot ( refDir,normal);
	Ray reflectRay = Ray( point , vec4 (refDir,0) );
	glm::vec3 hitpoint;
	shape* hitobj;
	bool hit = getClosestIntersect(hitobj, hitpoint,reflectRay);
	if(hit)
		return color + obj->specular * findColor(vec4(hitpoint,1),hitobj,reflectRay,++depth);
	else
		return color;
}