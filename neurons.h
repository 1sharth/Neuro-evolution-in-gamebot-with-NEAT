#pragma once
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utility.h"

struct Neuron
{
  int id;
  char type;
  double value;
  Link** linksout;
  Link** linksin;
  int linksoutsize,linksinsize;
  int posx,posy;
};typedef struct Neuron Neuron;

Neuron* newNeuron(char type,double value)
{
  Neuron* n=(Neuron*)malloc(sizeof(Neuron));
  n->id=newNeuronId();
  n->type=type;
  if(n->type=='I')
    {
      n->posx=-300;
      n->posy=y1;
      y1-=50;
    }
    else if(n->type=='O')
    {
      n->posx=300;
      n->posy=y3;
      y3-=40;
    }
    else
    {
      n->posx=rand()%200-100;
      n->posy=rand()%400-200;
    }
  n->value=value;
  n->linksout=NULL;
  n->linksin=NULL;
  n->linksoutsize=0;
  n->linksinsize=0;
  return n;
}

void neuronAddLink(Neuron* n,Link* l,char dir)
{
  if(dir=='I')
  {
    if(n->linksinsize==0)
    {
      n->linksin=(Link**)malloc(sizeof(Link*));
      n->linksin[0]=l;
      n->linksinsize++;
    }
    else
    {
      n->linksinsize++;
      n->linksin=(Link**)realloc(n->linksin,sizeof(Link*)*(n->linksinsize));
      n->linksin[n->linksinsize-1]=l;
    }
  }
  else
  {
    if(n->linksoutsize==0)
    {
      n->linksout=(Link**)malloc(sizeof(Link*));
      n->linksout[0]=l;
      n->linksoutsize++;
    }
    else
    {
      n->linksoutsize++;
      n->linksout=(Link**)realloc(n->linksout,sizeof(Link*)*(n->linksoutsize));
      n->linksout[n->linksoutsize-1]=l;
    }
  }
}
