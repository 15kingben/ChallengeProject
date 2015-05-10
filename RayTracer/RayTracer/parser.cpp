#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <deque>
#include "Camera.h"
#include "Light.h"
#include "shape.h"
#include "Circle.h"
#include "Triangle.h"
#include "Variables.h"
#include "Transform.h"

using namespace std;

bool readvals(stringstream &s, const int numvals, float* values) 
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i]; 
        if (s.fail()) {
            cout << "Failed reading value " << i << " will skip\n"; 
            return false;
        }
    }
    return true; 
}



void rightmultiply(const glm::mat4 & M, stack<glm::mat4> &transfstack) 
{
	//Ben's notes
	//In c++ all matrices are row major but in OpenGL they are column major, hence the tranpose call before adding to stack
	//this method adds a specific matrix to the overall transformation matrix including modelview perspective etc.
	//in the stack last in is first out so translate should go on after perspective
	//this is useful if all things have a modelview transform but only some things have a scale transform e.g.

    glm::mat4 &T = transfstack.top(); 
    T = M * T; 
}

void read(const char* filename){
	string str , cmd;
	ifstream sceneFile;
	sceneFile.open(filename);
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> vertNorms;
	Camera cam;
	std::stack <glm::mat4> transfstack;
	transfstack.push(glm::mat4(1.0));  // identity
	int vertCount = 0;
	getline(sceneFile,str);
	float linAtten = 0;
		float quadAtten = 0;
	float conAtten = 1;
	float ambient[3] ; 
	float diffuse[4] ; 
	float specular[4] ; 
	float emission[4] ; 
	float shininess ;
	while(sceneFile){

		if (   (str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')  ) {//rule out blank lines and comments
		stringstream s(str);
		s >> cmd;
		//std::cout << cmd << "\n";

		int i; 
                float values[10]; // Position and color for light, colors for others
                                    // Up to 10 params for cameras.  
                bool validinput; // Validity of input 

                // Process the light, add it to database.
                // Lighting Command
                if (cmd == "light") {
                    //if (numused == numLights) { // No more Lights 
                    //    cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
                    //} else {
                        validinput = readvals(s, 8, values); // Position/color for lights.
                        if (validinput) {

                            // YOUR CODE FOR HW 2 HERE. 
                            // Note that values[0...7] shows the read in values 
                            // Make use of lightposn[] and lightcolor[] arrays in variables.h
                            // Those arrays can then be used in display too.  
							// float[] lightposn = new float[3];//destroy
							// for(int i = 0; i < 3; i++){
							//	 lightposn[] = values[i];
							// }
							// for(int i = 4; i < 8; i++){
							//	 lightcolor[4*numused+i-4] = values[i];
							// }


                            //++numused; 
                        }
                    
                }else if(cmd == "camera"){
					validinput = readvals(s,10,values);
					if(validinput){
						scene.cam.lookFrom.x = values[0];
						scene.cam.lookFrom.y = values[1];
						scene.cam.lookFrom.z = values[2];
						scene.cam.lookAt.x = values[3];
						scene.cam.lookAt.y = values[4];
						scene.cam.lookAt.z = values[5];
						scene.cam.up.x = values[6];
						scene.cam.up.y = values[7];
						scene.cam.up.z = values[8];
						scene.cam.fovy = values[9];
					}
				
				
				}else if(cmd == "point"){
					glm::vec4 loc;
					glm::vec3 col;
					s >> loc.x;
					s >> loc.y;
					s >> loc.z;
					loc.w = 1;
					s >> col.x;
					s >> col.y;
					s >> col.z;
					scene.lights.push_back(Light(loc,col,conAtten,linAtten,quadAtten,Light::point));
				}else if(cmd == "directional"){
					glm::vec4 loc;
					glm::vec3 col;
					s >> loc.x;
					s >> loc.y;
					s >> loc.z;
					loc.w = 0;
					s >> col.x;
					s >> col.y;
					s >> col.z;
					scene.lights.push_back(Light(loc,col,conAtten,linAtten,quadAtten,Light::direction));
				}else if(cmd == "attenuation"){
					s >> conAtten;
					s >> linAtten;
					s >> quadAtten;
				}else if(cmd == "maxdepth"){
					validinput = readvals(s,1,values);
					if(validinput){
						scene.maxdepth = values[0];
					}
					
				}else if(cmd == "filename"){
					s >> scene.filename;
					

				}else if (cmd == "translate") {
                        validinput = readvals(s,3,values) ; 
                        if (validinput) {
							rightmultiply(Transform::translate(values[0], values[1], values[2]), transfstack);
                        }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s,3,values); 
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE.  
                        // Think about how the transformation stack is affected
                        // You might want to use helper functions on top of file.  
                        // Also keep in mind what order your matrix is!
						rightmultiply(Transform::scale(values[0],values[1],values[2]), transfstack);
                    }
                }
                else if (cmd == "rotate") {

                    validinput = readvals(s,4,values); 
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE. 
                        // values[0..2] are the axis, values[3] is the angle.  
                        // You may want to normalize the axis (or in Transform::rotate)
                        // See how the stack is affected, as above.  
                        // Note that rotate returns a mat3. 
                        // Also keep in mind what order your matrix is!

						//to convert Transform::rotate to mat3
						
						glm::mat3 rot = Transform::rotate(values[3], glm::vec3(values[0],values[1],values[2]) );
						glm::mat4 rot1(rot);
						rightmultiply(rot1, transfstack);
                    }

                }else if(cmd == "sphere"){
					validinput = readvals(s,4,values);
					if(validinput){
						glm::vec3 amb;
						glm::vec3 spec;
						glm::vec3 emiss;
						glm::vec3 diff;
						for(int i = 0; i < 3; i++){
							amb[i] = ambient[i];
							spec[i] = specular[i];
							emiss[i] = emission[i];
							diff[i] = diffuse[i];
						} 
						scene.objects.push_back(new Circle(values[0],values[1], values[2],values[3],transfstack.top(), amb, diff, spec, emiss, shininess));
					}
				}else if(cmd == "size"){
					s >> sceneWidth;
					s >> sceneHeight;
				}else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            ambient[i] = values[i]; 
                        }
                    }
                } else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            diffuse[i] = values[i]; 
                        }
                    }
                } else if (cmd == "specular") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            specular[i] = values[i]; 
                        }
                    }
                } else if (cmd == "emission") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            emission[i] = values[i]; 
                        }
                    }
                } else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values); 
                    if (validinput) {
                        shininess = values[0]; 
                    }
                
				
				
				}else if(cmd == "tri"){
					int ind1,ind2,ind3;
					s >> ind1;
					s >> ind2;
					s >> ind3;
					glm::vec3 v1,v2,v3;
					v1 = verts[ind1];
					v2 = verts[ind2];
					v3 = verts[ind3];

					glm::vec3 amb;
					glm::vec3 spec;
					glm::vec3 emiss;
					glm::vec3 diff;
					for(int i = 0; i < 3; i++){
						amb[i] = ambient[i];
						spec[i] = specular[i];
						emiss[i] = emission[i];
						diff[i] = diffuse[i];
					} 
					scene.objects.push_back(new Triangle(v1,v2,v3, transfstack.top(), amb, diff, spec, emiss, shininess));


				}else if(cmd == "trinormal"){
					int ind1,ind2,ind3;
					s >> ind1;
					s >> ind2;
					s >> ind3;
					glm::vec3 v1,v2,v3,n1,n2,n3;
					v1 = verts[ind1];
					v2 = verts[ind2];
					v3 = verts[ind3];
					n1 = vertNorms[ind1];
					n2 = vertNorms[ind2];
					n3 = vertNorms[ind3];
					glm::vec3 amb;
					glm::vec3 spec;
					glm::vec3 emiss;
					glm::vec3 diff;
					for(int i = 0; i < 3; i++){
						amb[i] = ambient[i];
						spec[i] = specular[i];
						emiss[i] = emission[i];
						diff[i] = diffuse[i];
					} 
					scene.objects.push_back(new Triangle(v1,v2,v3,n1,n2,n3,transfstack.top(), amb, diff, spec, emiss, shininess));
				}else if(cmd == "maxverts" || cmd == "maxvertnorms"){
					
				}else if (cmd == "vertex"){
					float x,y,z;
					s >> x;
					s >> y;
					s >> z;
					verts.push_back(glm::vec3(x,y,z));
					vertNorms.push_back(glm::vec3(1.0));
					vertCount++;
				}else if(cmd == "vertexnormal"){
					float x,y,z,nx,ny,nz;
					s >> x;
					s >> y;
					s >> z;
					s >> nx;
					s >> ny;
					s >> nz;
					verts.push_back(glm::vec3(x,y,z));
					vertNorms.push_back(glm::vec3(nx,ny,nz));
					vertCount++;
				}else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top()); 
                } else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n"; 
                    } else {
                        transfstack.pop(); 
                    }
                } else if(cmd == "output"){
					s >> outputFile;
				}

                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n"; 
                }



		}
			getline(sceneFile,str);

	}
	
	
	cin.get();
}