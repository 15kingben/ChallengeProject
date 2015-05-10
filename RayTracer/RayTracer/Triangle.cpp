#include "Triangle.h"
#include <iostream>
#include "Ray.h"

Triangle::Triangle(glm::vec3 newA, glm::vec3 newB, glm::vec3 newC,glm::mat4 trans,glm::vec3 amb, glm::vec3 diff,glm::vec3 spec,glm::vec3 emiss,float shine)
{
	a = newA;
	b = newB;
	c = newC;
	na = nb = nc = glm::cross(a-b,b-c);//pretty sure this is right
	transform = trans;
	transformInv = glm::inverse(trans);
	ambient = amb; 
	diffuse = diff;
	specular = spec; 
	emission = emiss;	
	shininess = shine; 
}

Triangle::Triangle(glm::vec3 newA, glm::vec3 newB, glm::vec3 newC,glm::vec3 _na, glm::vec3 _nb, glm::vec3 _nc, glm::mat4 trans,glm::vec3 amb, glm::vec3 diff,glm::vec3 spec,glm::vec3 emiss,float shine)
{
	a = newA;
	b = newB;
	c = newC;
	na = _na;
	nb = _nb;
	nc = _nc;
	transform = trans;
	transformInv = glm::inverse(trans);
	ambient = amb; 
	diffuse = diff;
	specular = spec; 
	emission = emiss;	
	shininess = shine; 
}

//glm::mat4 Triangle::getTransform(){
//
//	return glm::mat4(1);
//}


bool Triangle::Intersect(Ray ray,glm::vec3 &point){
	
	glm::vec3 normal = glm::cross((b-a),(c-a));
	if(glm::dot(glm::vec3(ray.direction),normal) == 0){
		return false;
	}
	ray.origin = ray.origin * transformInv;
	ray.origin /= ray.origin.w;
	ray.direction = ray.direction * transformInv;

	float t = ( glm::dot(a,normal) - glm::dot(glm::vec3(ray.origin),normal) ) / (glm::dot(glm::vec3(ray.direction),normal));
	if (t < 1e-2) {
        return false;
    }
	glm::vec3 p = glm::vec3(ray.origin) + glm::vec3(ray.direction) * t;
	glm::vec4 pTrans = glm::vec4(p,1	) * transform;
	pTrans /= pTrans.w;
	//p = glm::vec3(pTrans);
	float triArea = glm::length( glm::cross((b-a),(c-a)) )/2;
	float cap = glm::length(glm::cross((p-c),(c-a)))/2;
	if(glm::dot(glm::cross((p-c),(c-a)),normal) < 0)
		return false;
	float abp = glm::length(glm::cross((b-a),(p-a)))/2;
	if(glm::dot(glm::cross((b-a),(p-a)),normal) < 0)
		return false;
	float bcp = glm::length(glm::cross((c-b),(p-b)))/2;
	if(glm::dot(glm::cross((c-b),(p-b)),normal) < 0)
		return false;
	float u = cap / triArea;
	float v = abp / triArea;
	float w = bcp / triArea;
	//if(u > -.0001 && u < 1.0001 && v > -.0001 && v < 1.0001 && w > -.0001 && w < 1.0001 ){
		point = glm::vec3(pTrans);
		return true;
	//}else
		//return false;

		
	/*
	ray.origin = ray.origin * transformInv;
	ray.origin /= ray.origin.w;
	ray.direction = ray.direction* transformInv;

	glm::vec3 n = glm::cross(b-a, c-a);
    const glm::vec3& p = glm::vec3(ray.origin);
    const glm::vec3& dir = glm::vec3(ray.direction);
    
    // Ray parallel with plane
    if ((glm::dot(dir, n)) == 0) {
        return false;
    }
    
    //plane ray intersection -- (p+dir*t)*n = a*n;
    float t = (glm::dot(a,n) - glm::dot(p,n)) / glm::dot(dir,n);
    glm::vec3 p0 = p + (dir * t);
    
    if (t < 1.0e-2) {
        if (t > 0) {
            //printf("triangle near zero = %f\n", t);
        }
        return false;
    }
    // check if p0 in triangle, because triangle is convex.
    // if p0 in triangle, then absolute area equals to area_vec length, otherwise not.
    
    glm::vec3 area_vec(0,0,0);
    float abs_area = 0.0;
	glm::vec3 vertexes[3];
	vertexes[0] = a;
	vertexes[1] = b;
	vertexes[2] = c;
    for (int i = 0; i < 3; ++i) {
        abs_area += glm::length(glm::cross(p0-vertexes[i], p0-vertexes[(i+1)%3]));
        area_vec += glm::cross(p0-vertexes[i], p0-vertexes[(i+1)%3]);
    }
    
    glm::vec3 tmp_nb = glm::cross(c-p0, a-p0);
    glm::vec3 tmp_nc = glm::cross(a-p0, b-p0);
    
    float beta = glm::dot(n, tmp_nb) / glm::dot(n, n);
    float gamma = glm::dot(n, tmp_nc) / glm::dot(n, n);
    float alpha = 1.0 - beta - gamma;
    
	float* dis_to_ray;
    if (beta > -.00001 && beta < 1.0+.00001 && gamma > -.0001 && gamma < 1.0+.00001 
        && alpha > -.0001 && alpha < 1.0+.0001) {
        //*dis_to_ray = t;
        return true;
    } else
        return false;*/




}

glm::vec3 Triangle::getNormal(glm::vec3 point)
{
	if(na == nb && nb == nc){//triangle
		glm::vec4 norma = glm::vec4(na,0.0f) * glm::transpose(transformInv);
		//norma /= norma.w;
		return glm::vec3(norma);
	}else{//trinormal

		glm::vec4 p = glm::vec4(point,1) * transformInv;
		p /= p.w;
    glm::vec3 n = glm::cross(b-a, c-a);
    glm::vec3 tmp_nb = glm::cross(c-glm::vec3(p), a-glm::vec3(p));
    glm::vec3 tmp_nc = glm::cross(a-glm::vec3(p), b-glm::vec3(p));
    
    float beta = glm::dot(n, tmp_nb) / glm::dot(n,n);
    float gamma = glm::dot(n, tmp_nc) / glm::dot(n,n);
    float alpha = 1.0 - beta - gamma;
    glm::vec3 ret = (na * alpha) + (nb * beta) + (nc * gamma);
	return glm::vec3(glm::vec4(ret, 0.0f) * glm::transpose(transformInv));
	
	//normal = glm::vec3(glm::normalize(glm::cross((tri->c - tri->a),(tri->b - tri->a))));
	//normal = glm::vec3(glm::vec4(normal,0) * glm::transpose(tri->transformInv)  );
	
	}
}


Triangle::~Triangle(void)
{
}
