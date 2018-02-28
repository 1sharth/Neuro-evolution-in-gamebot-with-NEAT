#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "utility.h"
#include "global.h"
#include "geneticelements.h"

//size of queue is limited
struct Queue
{
  int r,f;
  Neuron* data[5000];
};typedef struct Queue Queue;

void queueInit(Queue* q)
{
  q->f=0;
  q->r=0;
}

short qpush(Queue* q,Neuron* n)
{
  q->data[q->r]=n;
  q->r++;
  return 1;
}

Neuron* qpop(Queue* q)
{
  if(q->r==q->f)
  {
    printf("underflow in queue\n");
    fflush(stdout);
  }
  Neuron* n=q->data[q->f];
  q->f++;
  return n;
}

void queueDisplay(Queue* q)
{
  int i;
  for(i=q->f;i<q->r;i++)
  {
    printf("%d ",q->data[i]->id);
  }
}

short qEmpty(Queue* q)
{
  return (q->f)==(q->r);
}

int queueSize(Queue* q)
{
  return q->r-q->f;
}
