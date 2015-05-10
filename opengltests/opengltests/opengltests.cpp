// opengltests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <Gl/glut.h>
#include <gl/glu.h>

void render(void) 
{


	double numBoxesWidth = 5;
	double width = 2 - .1;//space on edge
	double boxSize = width/numBoxesWidth - .1;
  glClearColor(1.0,1.0,1.0,1.0); 
  glColor3f(0.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
  
  for(double x = -1 + boxSize + .2; x < 1; x += boxSize){
	  for( double y = -1 + boxSize + .2; y < 1; y +=boxSize){
		glBegin(GL_LINE_LOOP);

		glVertex3f(x + boxSize/2, y+boxSize/2,0.0);
		glVertex3f(x + boxSize/2, y-boxSize/2,0.0);
		glVertex3f(x - boxSize/2, y-boxSize/2,0.0);
		glVertex3f(x - boxSize/2, y+boxSize/2,0.0);
		glEnd();
		glFlush();
		//int g;
		//std::cin >> g ;
		std::cout << x << " " <<y << " "<< boxSize << " ";
		y+=.1;
	  }
	  x+=.1;
  }
  
  
}

void main(int argc, char **argv) 
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(500,500);
  glutCreateWindow("My First openGL Program");
  glutDisplayFunc(render);
  glutMainLoop();
}