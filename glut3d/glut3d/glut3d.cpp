// example of MouseAction and glutFullScreen

#include "stdafx.h"
#include <iostream>
#include <GL/glut.h> 
#include <math.h>

 GLfloat yang = 0.2; 
 GLfloat r,g,b = 0.5;
 GLfloat p,q   = 0.5;
 int fullscreen = 1;

 void MouseAction(int the_button, int button_state, int x, int y){
         if (the_button==GLUT_LEFT_BUTTON && button_state==GLUT_DOWN){
            if (fullscreen==1){
                 glutReshapeWindow(640,480);
            }else{
                glutFullScreen();
            }
            fullscreen = 1-fullscreen;
    }
 }

 void display()  
 {  
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);  
    r=r+(((float)rand()/(float)RAND_MAX)*0.05-0.025);
    if (r<0.0) r=0.0;
    if (r>1.0) r=1.0;
    g=g+(((float)rand()/(float)RAND_MAX)*0.05-0.025);
    if (g<0.0) g=0.0;
    if (g>1.0) g=1.0;
    b=b+(((float)rand()/(float)RAND_MAX)*0.05-0.025);
    if (b<0.0) b=0.0;
    if (b>1.0) b=1.0;
    p=p+(((float)rand()/(float)RAND_MAX)*0.05-0.025);
    if (p<0.0) p=0.0;
    if (p>1.0) p=1.0;
    q=q+(((float)rand()/(float)RAND_MAX)*0.05-0.025);
    if (q<0.0) q=0.0;
    if (q>1.0) q=1.0;
    glBegin(GL_POLYGON);  
       glColor3f(r,1-b,0.0);  
       glVertex2f(-1.0,-1.0); 
       glColor3f(0,q-r,q);
       glVertex2f(-1.0,0.0);
       glColor3f(0.0,g,0.0);  
       glVertex2f(-1.0,1.0); 
       glColor3f(0.0,p,1.0-p);
       glVertex2f(0.0,1.0);
       glColor3f(b,r,g);
       glVertex2f(1.0,1.0); 
       glColor3f(q,0.0,r);
       glVertex2f(1.0,0.0);
       glColor3f(1.0-b,0.0,b);  
       glVertex2f(1.0,-1.0); 
       glColor3f(g,g,1.0-b);
       glVertex2f(0.0,-1.0);
    glEnd();  
    glutSwapBuffers(); 
    glFlush();
    glutMouseFunc(MouseAction);
 }  

 void init()  
 {  
    glClearColor(1.0,1.0,1.0,1.0);  
    glMatrixMode(GL_PROJECTION);  
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  
 }  
   

 void main(int argc, char** argv)  
 {  
    glutInit(&argc,argv);  
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowSize(400,400);  
    glutInitWindowPosition(0,0);  
    glutCreateWindow("PSI 01"); 
    glutFullScreen();
    glutDisplayFunc(display);  
    glutIdleFunc(display); 
    init();  
    glutMainLoop();  
 }