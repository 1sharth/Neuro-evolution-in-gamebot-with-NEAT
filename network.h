#pragma once
#include "headerfiles.h"

double* output=NULL;

double nodeVal(Genome* g,Neuron* n)
{
  if(n->done)
  {
    //printf("node type:%c nodeval:%f\n",n->type,n->value);
    return n->value;
  }
  else
  {
    int i;
    double sum=0;
    for(i=0; i<n->linksinsize;i++)
    {
      sum+=nodeVal(g,g->nlist[n->linksin[i]->out])*(n->linksin[i]->weight);
    }
    n->value=activationFunc(sum);
    n->done=1;
    //printf("node type:%c nodeval:%f\n",n->type,n->value);
    return n->value;
  }
}

double* evalNetwork(Genome* g,double* inp)
{
  int i;
  //printf("from evalNetwork: inp[0]:%f inp[1]:%f\n",inp[0],inp[1]);
  for(i=0;i<global.totalinputs; i++)
  {
    g->nlist[i]->value=inp[i];
  }

  for(i=global.totalinputs;i<global.totalinputs+global.totaloutputs;i++)
  {
    //printf("%c\n",g->nlist[i]->type);fflush(stdout);
    g->nlist[i]->value=nodeVal(g,g->nlist[i]);
  }

  //printf("actually came out\n");fflush(stdout);
  output=(double*)realloc(output,sizeof(double)*global.totaloutputs);
  int k=0;
  for(i=global.totalinputs;i<global.totalinputs+global.totaloutputs;i++)
  {
    if(g->nlist[i]->type!='O')
    {printf("not output node sucker: evalnetwork\n");}
    output[k++]=g->nlist[i]->value;
  }
  return output;

}

void makeNetwork(Genome* genome)
{
  clearAllCircles();
  clearAllLines();
  for(int i=0; i<genome->nlistsize; i++)
  {
    Neuron* n=genome->nlist[i];
    Circle* c=addCircle(n->posx,n->posy,5,&black);
    c->windowId=2;

  }
  for(int i=0; i<genome->llistsize; i++)
  {
    Neuron* n1=genome->nlist[genome->llist[i]->out];
    Neuron* n2=genome->nlist[genome->llist[i]->in];
    if(genome->llist[i]->enable)
    {
      Line* l=addLine(n1->posx,n1->posy,n2->posx,n2->posy,&green);
      l->windowId=2;
    }
    else
    {
      Line* l=addLine(n1->posx,n1->posy,n2->posx,n2->posy,&red);
      l->windowId=2;
    }
  }

}


