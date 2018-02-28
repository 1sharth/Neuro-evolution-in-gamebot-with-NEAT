#pragma once
#include "headerfiles.h"

int frames=0;

double* inp=NULL;
double* out=NULL;

double* getInput()
{
  inp=(double*)realloc(inp,sizeof(double)*global.totalinputs);
  /*inp[0]=tan((double)(rect_arr[bulletind].y-rect_arr[playerind].y)/(double)(rect_arr[bulletind].x-rect_arr[playerind].x));
  if(inp[0]>5)
    inp[0]=5;*/
  inp[0]=atanf((double)(rect_arr[bulletind].y-rect_arr[playerind].y)/(double)(rect_arr[bulletind].x-rect_arr[playerind].x));
  inp[1]=(((double)(rect_arr[bulletind].y-rect_arr[playerind].y))/((double)(windowup-windowdown)));

  //print("inp:%f\n",inp[0]);
  //inp[0]=getRandomfd(-1,1);
  //inp[1]=getRandomfd(-1,1);
  return inp;
}

void renderFunction()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0,0,0);
  if(drawinwindowone)
    drawEverything(1);
  glutSwapBuffers();

  double *out,fit;
  int yy;

    inp=getInput();

    //printf("inputs%f\n",inp[0]);fflush(stdout);
    out=evaluateCurrent(inp);

    //printf("outputs%f %f\n",out[0],out[1]);fflush(stdout);
    if(out[0]>out[1])
      yy=10;
    else if(out[0]==out[1])
      yy=0;
    else
      yy=-10;

  //yy=(int)(8*(out[0]-out[1]));
  //printf("%d\n",(int)(4*(out[0]-out[1])));fflush(stdout);
  frames=(frames+1)%4;
  playerDynamics(0,yy);
  if(bulletDynamicsAndCollision()==1)
  {
    bulletPlayerReset();
    if (advanceIndividual() == '1')
    {
      drawinwindowone=0;
      newGeneration();
      global.maxfitness = 0.0;
      drawinwindowone=1;
    }
  }
  else
  {
    fit=(slist[global.curr_species]->glist[global.curr_genome]->fitness);
    if(rect_arr[playerind].y+rect_arr[playerind].h/2<rect_arr[bulletind].y-rect_arr[bulletind].h/2 || rect_arr[playerind].y-rect_arr[playerind].h/2>rect_arr[bulletind].y+rect_arr[bulletind].h/2)
    {
      (slist[global.curr_species]->glist[global.curr_genome]->fitness+=2.0);
      fit+=2.0;
    }
    if(fit>global.maxfitness)
      global.maxfitness=fit;
  }
  if(drawinwindowone)
    glutPostRedisplay();
}

void idle1()
{

}

void renderFunction2()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0,0,0);
  /*if(drawinwindowone)
    makeNetwork(slist[global.curr_species]->glist[global.curr_genome]);*/
  //mutate(glist[0]);
  makeNetwork(glist[0]);
  drawEverything(2);
  glutSwapBuffers();
  //if(drawinwindowone)
  glutPostRedisplay();
}

void idle2()
{

}

void onKeyPress(unsigned char key,int x,int y)
{
  switch(key)
  {
    case 'w':moveRect(&rect_arr[playerind],0,12); break;
    case 's':moveRect(&rect_arr[playerind],0,-12); break;
    case 'd': drawinwindowone=drawinwindowone?0:1; break;
  }
}