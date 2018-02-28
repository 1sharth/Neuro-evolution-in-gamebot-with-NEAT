#pragma once
#include "headerfiles.h"

short FIXED_NEURAL_NET=0;

struct Global
{
  int totalinputs;
  int totaloutputs;
  int population;
  double maxfitness;
  int curr_genome;
  int curr_species;
  int curr_gen;
};typedef struct Global Global;

Global global;

void globalize()
{
    global.totalinputs=2;
    global.totaloutputs=2;
    global.population=80;
    global.maxfitness=0;
    global.curr_genome=0;
    global.curr_species=0;
    global.curr_gen=0;
}

int INITIALWEIGHT=1;

struct Itable
{
  int innovationid;
  char type;
  int out,in;
};typedef struct Itable Itable;
Itable* itable;
int itable_size=0;

int newInnovation(char type,int out,int in)
{
    if(itable_size==0)
    {
        itable_size++;
        itable=(Itable*)malloc(sizeof(Itable));
    }
    else
    {
        itable_size++;
        itable=(Itable*)realloc(itable,sizeof(Itable)*itable_size);
    }

    itable[itable_size-1].innovationid=itable_size-1;
    itable[itable_size-1].type=type;
    itable[itable_size-1].out=out;
    itable[itable_size-1].in=in;

    return itable_size-1;
}

int checkInnovation(char type,int out,int in)
{
    int i;
    for(i=0; i<itable_size; i++)
    {
        if(itable[i].type==type && itable[i].out==out && itable[i].in==in)
        {
            return i;
        }

    }
    return -1;
}




