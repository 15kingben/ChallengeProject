// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.
#include <stdio.h>
#include <iostream>
#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    /*// YOUR CODE FOR HW1 HERE
	float radian = degrees*pi/180;
	mat3 mat(1,0,0,  0,1,0, 0,0,1);
	mat = mat * cos(degrees*pi/180);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	mat3 matx(x*x, x*y, x*z,
              x*y, y*y, y*z,
              x*z, y*z, z*z);
	mat3 aStar(0.0,  -z,   y,   
			     z, 0.0,  -x,
				-y,   x, 0.0);

	vec3 axis1 = axis;
	mat = cos(radian) * mat3(1.0) + (1.0-cos(radian)) * matx + sin(radian) * aStar;
	//mat3 mat1 = glm::transpose(axis1)*axis;
	//mat = mat + (1-cos(degrees*pi/180))*matx + sin(degrees/180*pi)*mat3(0,axis.z,axis.y*-1,  axis.z*-1,0,axis.x,  axis.y,axis.x*-1,0);
	

  // You will change this return call
  return mat;*/


  // YOUR CODE FOR HW2 HERE
        float radian = degrees / 180.0 * pi;
        float x = axis.x, y = axis.y, z = axis.z;
        mat3 Identity;
        mat3 aa(x*x, x*y, x*z,
                        x*y, y*y, y*z,
                        x*z, y*z, z*z);
        mat3 Astar(0.0, -z, y,
                           z, 0.0, -x,
                           -y, x, 0.0);
        mat3 result = cos(radian) * Identity + (1.0 - cos(radian)) * aa +  sin(radian) * Astar;
        return result;  
}


// Transforms the camera up around the "crystal ball" interface

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 

	ret = mat4(sx, 0.0, 0.0, 0.0,  
			    0.0, sy, 0.0, 0.0,
			    0.0, 0.0, sz, 0.0,
			    0.0, 0.0, 0.0, 1.0);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    // YOUR CODE FOR HW2 HERE
        return mat4(1.0, 0.0, 0.0, tx,
                    0.0, 1.0, 0.0, ty,
                    0.0, 0.0, 1.0, tz,
                    0.0, 0.0, 0.0, 1.0);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or 
//.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
