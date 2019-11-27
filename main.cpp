#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include "Bezier.h"
#include "CurveManager.h"

void init();
void display();
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void check();
void reshape(int width, int height);
void idle();
void arrowkey(int key, int x, int y);
void draw_pix(float x, float y, float r, float g, float b);
void pix_to_norm(float* x, float* y);

int screen_width = 500;
int screen_height = 500;

std::vector<CurveManager> cm;

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(screen_width, screen_height);
  glutCreateWindow("Project 2");

  /*defined glut callback functions*/
  glutDisplayFunc(display); //rendering calls here
  glutMouseFunc(mouse);     //mouse button events
  glutKeyboardFunc(key);    //Keyboard events
  //glutIdleFunc(idle);       //Function called while program is sitting "idle"
  glutSpecialFunc(arrowkey);

  //initialize opengl variables
  init();

  cm.emplace_back();

  //start glut event loop
  glutMainLoop();

  return 0;
}

/*initialize gl stufff*/
void init()
{
  //set clear color (Default background to white)
  glClearColor(1.0,1.0,1.0,1.0);
  //checks for OpenGL errors
  check();
}

/*Gets called when display size changes, including initial craetion of the display*/
void reshape(int width, int height) {
  /*set up projection matrix to define the view port*/
  //update the ne window width and height
  screen_width = width;
  screen_height = height;

  //creates a rendering area across the window
  glViewport(0,0,width,height);
  // up an orthogonal projection matrix so that
  // the pixel space is mapped to the grid space
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,screen_width,0,screen_height,-10,10);

  //clear the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //set pixel size relative to the grid cell size
  glPointSize(1);
  //check for opengl errors
  check();
}

//called repeatedly when glut isn't doing anything else
void idle() {
  //redraw the scene over and over again
  //glutPostRedisplay();
}

//this is where we render the screen
void display() {
  //clears the screen
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
  //clears the opengl Modelview transformation matrix
  glLoadIdentity();

  cm[0].displayCurves();

  //blits the current opengl framebuffer on the screen
  glutSwapBuffers();
  //checks for opengl errors
  check();
}

//gets called when a key is pressed on the keyboard
void key(unsigned char ch, int x, int y)
{
  switch (ch) {
    case '\t':
      cm[0].selectNextCurve();
      break;
    case 'n':
      cm[0].addCurve();
      break;
    case 'd':
      cm[0].deletePoint();
      break;
    case 'm':
      cm[0].toggleModifying();
    default:
      break;
  }
  //redraw the scene after keyboard input
  glutPostRedisplay();
}

//gets called when a mouse button is pressed
void mouse(int button, int state, int x, int y)
{
  if(state !=GLUT_DOWN) {  //button released
    //std::cout << x << " " << y << "\n";
    float xf = x;
    float yf = y;

    pix_to_norm(&xf, &yf);

    if (cm[0].isModifying()) {
      cm[0].modifyPoint(xf, yf);
    } else {
      cm[0].addPoint(xf, yf);
    }
  }

  glutPostRedisplay();
}

//checks for any opengl errors in the previous calls and
//outputs if they are present
void check()
{
  GLenum err = glGetError();
  if(err != GL_NO_ERROR)
  {
    printf("GLERROR: There was an error %s\n",gluErrorString(err) );
    exit(1);
  }
}

void pix_to_norm(float* x, float* y) {
  *x = (*x / screen_width - 0.5f) * 2.0f;
  *y = -(*y / screen_width - 0.5f) * 2.0f;
}

/*void draw_pix(float x, float y, float r, float g, float b){
  glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex3f(pix_to_norm(x), pix_to_norm(y), 0);
  glEnd();
}*/

void arrowkey(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_RIGHT:
      cm[0].selectNextPoint();
      break;
    case GLUT_KEY_LEFT:
      cm[0].selectPreviousPoint();
    default:
      break;
  }

  glutPostRedisplay();
}