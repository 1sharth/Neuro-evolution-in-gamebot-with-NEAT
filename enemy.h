#pragma once
#include "rectangle.h"
#include "gwindow.h"
/*
-----------Never used---------
enemies not added yet
*/
void generateEnemies(int rows,int cols)
{
  int i,j,x=100,y=windowup-50;
  for(j=1; j<=cols; j++)
  {
    if(j&1) y=windowup-100;
    else y=windowup-130;
    for(i=1; i<=rows; i++)
    {
      addRectangle(x,y,20,20);
      y-=50;
    }
    x+=80;
  }
}
