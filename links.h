#pragma once
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utility.h"

struct Link
{
  int in,out;
  double weight;
  short enable;
  int innovation;
};typedef struct Link Link;

Link* newLink(int out,int in, double w)
{
  Link *l=(Link*)malloc(sizeof(Link));
  l->in=in;
  l->out=out;
  l->enable=1;
  l->weight=w;
  l->innovation=newInnovation();
  return l;
}
