#pragma once
#include <GL/freeglut.h>
int CurrentWidth = 512,CurrentHeight = 400;
int CurrentWidth2 = 512,CurrentHeight2 = 400;
int windowup;
int windowdown;
int windowleft;
int windowright;
int drawinwindowone=1;

struct Color
{
  int r,g,b;
};typedef struct Color Color;

Color black={0,0,0},red={255,0,0},green={0,255,0};

void renderFunction();
void renderFunction2();
void onMouseHandling(int ,int , int , int );
void onKeyPress(unsigned char,int,int);
void onMouseHandling2(int ,int , int , int );
void idle1();
void idle2();
void Initialize(int argc,char** argv)
{
  windowup=(int)(CurrentHeight*0.6/2);
  windowdown= (int)(-CurrentHeight*0.6/2);
  windowleft= (int)(-CurrentWidth*0.8/2);
  windowright= (int)(CurrentWidth*0.8/2);
  printf("%d %d %d %d\n",windowup,windowdown,windowleft,windowright);
  glutInit(&argc, argv);

  glutInitWindowSize(CurrentWidth, CurrentHeight);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutCreateWindow("window1");
  glutDisplayFunc(renderFunction);
  glutMouseFunc(onMouseHandling);
  glutIdleFunc(idle1);
  glutKeyboardFunc(onKeyPress);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  gluOrtho2D(-CurrentWidth/2,CurrentWidth/2,-CurrentHeight/2,CurrentHeight/2);


  glutInitWindowSize(CurrentWidth2, CurrentHeight2);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  //glutInitWindowPosition(1000,1000);
  glutCreateWindow("window2");
  glutDisplayFunc(renderFunction2);
  glutMouseFunc(onMouseHandling2);
  glutIdleFunc(idle2);
  //glutKeyboardFunc(onKeyPress);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  gluOrtho2D(-CurrentWidth2/2,CurrentWidth2/2,-CurrentHeight2/2,CurrentHeight2/2);

}
