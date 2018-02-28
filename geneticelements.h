#pragma once
#include "headerfiles.h"

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
  int i=checkInnovation('L',out,in);
  if(i!=-1)
  {
    l->innovation=i;
  }
  else
  {
    l->innovation=newInnovation('L',out,in);
  }
  return l;
}

//deep copy
void addToLinkArr(Link*** Larr,Link* l,int size)                      //called from breed()
{
  if(size==0)
  {
    size++;                                       //useless variable actually
    *Larr=(Link**)malloc(sizeof(Link*));
  }
  else
  {
    size++;
    *Larr=(Link**)realloc(*Larr,sizeof(Link*)*size);
  }
  (*Larr)[size-1]=NULL;
  (*Larr)[size-1]=(Link*)realloc((*Larr)[size-1],sizeof(Link));
  *((*Larr)[size-1])=*l;              //deep copy
}

struct Neuron
{
  int id;
  char type;
  double value;
  double actvalue;
  short done;
  Link** linksout;
  Link** linksin;
  int linksoutsize,linksinsize;
  int posx,posy;
};typedef struct Neuron Neuron;

int globaly1,globaly3;                   //TODO: remove hardcoded

void neuronPositionsInit()
{
  globaly1=windowup-windowup/2;
  globaly3=windowup-200;
}

Neuron* newNeuron(char type,double value)
{
  Neuron* n=(Neuron*)malloc(sizeof(Neuron));
  n->id=-1;
  n->type=type;

  if(n->type=='I')
  {
    n->posx=windowleft;
    n->posy=globaly1;
    globaly1-=50;
    n->done=1;
  }
  else if(n->type=='O')
  {
    n->posx=windowright;
    n->posy=globaly3;
    globaly3-=40;
    n->done=0;
  }
  else
  {
    n->posx=rand2()%200-100;
    n->posy=rand2()%(windowup-windowdown)+windowdown;
    n->done=0;
  }
  n->value=value;
  n->linksout=NULL;
  n->linksin=NULL;
  n->linksoutsize=0;
  n->linksinsize=0;
  return n;
}

void neuronPositionReset()
{
  neuronPositionsInit();
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



