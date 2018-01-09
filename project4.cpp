#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "glut.h"
#include "project4.h"

using namespace std;

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, float(w)/float(h), 1.0, 100.0);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
  GLfloat specular[]  = {1.0, 1.0, 1.0, 1.0};
  GLfloat shininess[] = {50.0};
  GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat no_shine[] = { 0.0 };
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Generate specular material properties:
  //glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  // Draw the first sphere:
  glTranslatef(-1.5, 0, -8);
  glutSolidSphere(1.0, 12, 12); 
  
  // Done with that, clear the modelview matrix
  glLoadIdentity();

  // Draw the second sphere:
  glTranslatef(1.5, 0, -8);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shine);

  glutSolidSphere(1.0, 12, 12); 
  
  glutSwapBuffers();
}

int main(int argc, char *argv[])
{
  GLfloat light0_position[] = {5.0, 5.0, 3.0, 0.0};
  GLfloat ambient[]         = {0.2, 0.2, 0.2, 1.0};  // default ambient color for all light sources
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(512, 512);         // set initial window size
  glutCreateWindow("Two Spheres");      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable z-buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glEnable(GL_LIGHTING);                              // enables lighting; this changes the behavior of glColor
  glEnable(GL_LIGHT0);                                // enable a light source; otherwise you will only see ambient light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);  // set the default ambient color
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);  // allow glColor to set ambient and diffuse colors of geometry
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
    
  glutMainLoop();
  return 0;
}

