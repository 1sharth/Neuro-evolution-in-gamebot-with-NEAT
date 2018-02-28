#pragma once
#include "headerfiles.h"

double* evaluateCurrent(double* inp)
{
  Species* s=slist[global.curr_species];
  Genome* g=s->glist[global.curr_genome];
  double* out=evalNetwork(g,inp);
  return out;
}

char advanceIndividual()
{
  Species* s=slist[global.curr_species];
  s->glist[global.curr_genome]->fitness/=s->glistsize;
  global.curr_genome++;
  if(global.curr_genome==s->glistsize)
  {

    int i;
    double max=0,sum=0;
    for(i=0; i<s->glistsize; i++)
    {
      if(max < s->glist[i]->fitness)
        max=s->glist[i]->fitness;
      sum+=s->glist[i]->fitness;
    }
    s->thisgenmaxfitness=max;
    s->sum_adj_fitness=sum;

    if(s->thisgenmaxfitness > s->maxfitness)
      s->maxfitness=s->thisgenmaxfitness;

    global.curr_species++;
    global.curr_genome=0;
    if(global.curr_species==slistsize)
    {
      global.curr_species=0;
      return '1';
    }
  }
  return '0';
}