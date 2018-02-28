#pragma once
#include "headerfiles.h"
typedef void (*Drawables)();
Drawables drawable_arr[100];
int drawable_count=3;

void drawEverything(int id)
{
  int i=0;
  for(i=0; i<drawable_count;i++)
    (drawable_arr[i])(id);
}


